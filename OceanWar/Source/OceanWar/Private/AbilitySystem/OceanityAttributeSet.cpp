// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/OceanityAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "OceanityGameTags.h"
#include "AbilitySystem/FunctionLibraries/OceanityAbilityFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "Log/OceanityLogChannels.h"
#include "Net/UnrealNetwork.h"

UOceanityAttributeSet::UOceanityAttributeSet()
{
	// Vital Attributes
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Vital::Tag_Vital_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Vital::Tag_Vital_Health, GetHealthAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Vital::Tag_Vital_Shield, GetShieldAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Vital::Tag_Vital_MaxShield, GetMaxShieldAttribute);

	// Primary Attributes
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Primary::Tag_Primary_Damage, GetDamageAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Primary::Tag_Primary_Ammo, GetAmmoAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Primary::Tag_Primary_MaxAmmo, GetMaxAmmoAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Primary::Tag_Primary_ReloadSpeed, GetReloadSpeedAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Primary::Tag_Primary_ShootCooldown,
	                     GetShootCooldownAttribute);

	// Secondary Attributes
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_MaxSpeed, GetMaxSpeedAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_Acceleration,
	                     GetAccelerationAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_TurnSpeed, GetTurnSpeedAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_Weight, GetWeightAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_BackwardsMultiplier,
	                     GetBackwardsMultiplierAttribute);

	// Boost Attributes
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Boost::Tag_Boost_BoostDuration, GetBoostDurationAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Boost::Tag_Boost_BoostCooldown, GetBoostCooldownAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Boost::Tag_Boost_BoostSpeed, GetBoostSpeedAttribute);

	// Meta Attributes
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Meta::Tag_Meta_IncomingCoins, GetIncomingCoinsAttribute);
	TagsToAttributes.Add(OceanityGameplayTags::Attribute::Meta::Tag_Meta_IncomingDamage, GetIncomingDamageAttribute);
}


void UOceanityAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetAmmoAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxAmmo());
	}
	else if (Attribute == GetShieldAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxShield());
	}
}

void UOceanityAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		UE_LOG(LogOceanityGAS, Warning, TEXT("Health: %f"), GetHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetAmmoAttribute())
	{
		SetAmmo(FMath::Clamp(GetAmmo(), 0.0f, GetMaxAmmo()));
	}
	else if (Data.EvaluatedData.Attribute == GetShieldAttribute())
	{
		SetShield(FMath::Clamp(GetShield(), 0.0f, GetMaxShield()));
	}
	else if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute() && Data.EvaluatedData.Magnitude > 0.f)
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		float AppliedDamage = LocalIncomingDamage;
		float EarnedMoney = AppliedDamage * 10.f;
		SetIncomingDamage(0.f);
		bool bIsDead = false;

		FGameplayTagContainer DamageTags;

		if (GetShield() > 0.f)
		{
			/*
			*	If we have shield, remove the damage from there first
			*	If there is still damage left over, ignore the rest since it's been absorbed by shield
			*/
			const float OldShield = GetShield();
			const float NewShield = FMath::Max(0.f, GetShield() - LocalIncomingDamage);
			// New Shield should be 0 or greater
			SetShield(NewShield);
			AppliedDamage = OldShield - NewShield;

			if (GetShield() > 0.f)
			{
				// Shield is still up, damage was absorbed
				DamageTags.AddTag(OceanityGameplayTags::Damage::Event::Hit::Tag_Hit_Shield);
			}
			else
			{
				DamageTags.AddTag(OceanityGameplayTags::Damage::Event::Hit::Tag_Hit_DestroyShield);
			}
		}
		else
		{
			/*
			*	No shield, take health damage
			*/
			const float OldHealth = GetHealth();
			const float NewHealth = FMath::Max(0.f, GetHealth() - LocalIncomingDamage);
			// New Health should be 0 or greater
			SetHealth(NewHealth);
			AppliedDamage = OldHealth - NewHealth;

			bIsDead = GetHealth() <= 0.f;
			if (bIsDead)
			{
				DamageTags.AddTag(OceanityGameplayTags::Damage::Event::Hit::Tag_Hit_Dead);
			}
		}
			
		/*
		 * Only show damage numbers for players and only if the source is not the target
		 * We dont want to show damage numbers for damage we do to ourselves
		*/

		if (Props.SourceCharacter->IsPlayerControlled() && Props.SourceCharacter != Props.TargetCharacter)
		{
			UAbilitySystemComponent* ASC = Data.EffectSpec.GetEffectContext().GetOriginalInstigatorAbilitySystemComponent();
			AActor* SourceActor = ASC ? ASC->AbilityActorInfo->AvatarActor.Get() : nullptr;
			FGameplayEffectContextHandle ContextHandle = Data.EffectSpec.GetContext();
			
			/** Get Coins earned based on Damage Tags */
			EarnedMoney += UOceanityAbilityFunctionLibrary::GetEarnedCoins(this, DamageTags);

			const FVector RandomLocation = FVector(
				FMath::FRandRange(-50.f, 50.f),
				FMath::FRandRange(-50.f, 50.f),
				FMath::FRandRange(-50.f, 50.f));

			FGameplayCueParameters CueParams;
			CueParams.Location = RandomLocation;
			CueParams.RawMagnitude = AppliedDamage;
			CueParams.NormalizedMagnitude = AppliedDamage;
			CueParams.TargetAttachComponent = Props.TargetCharacter->GetRootComponent();
			CueParams.EffectContext = Data.EffectSpec.GetContext();
			CueParams.SourceObject = Props.TargetCharacter;
			CueParams.Instigator = SourceActor;
			CueParams.AggregatedTargetTags = DamageTags;

			ASC->ExecuteGameplayCue(
				FGameplayTag::RequestGameplayTag(FName("GameplayCue.GameplayEvent.Hit.Success"), true), CueParams);

			if (EarnedMoney > 0.f) //TODO: Negative Money should be possible
			{
				FGameplayEventData EventData;
				EventData.EventMagnitude = EarnedMoney;
				EventData.TargetTags = FGameplayTagContainer(OceanityGameplayTags::Attribute::Meta::Tag_Meta_IncomingCoins);

				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
					SourceActor,
					OceanityGameplayTags::Gameplay::Event::Hit::Tag_Hit_Success,
					EventData);	
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetIncomingCoinsAttribute())
	{
		const float LocalIncomingCoins = GetIncomingCoins();

		if (LocalIncomingCoins == 0.f) return;
		SetIncomingCoins(0.f);
		UE_LOG(LogOceanityGAS, Warning, TEXT("Incoming Coins: %f"), LocalIncomingCoins);
	}
}


void UOceanityAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, Health, OldHealth);
}

void UOceanityAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, MaxHealth, OldMaxHealth);
}

void UOceanityAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, Shield, OldShield);
}

void UOceanityAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, MaxShield, OldShield);
}

void UOceanityAttributeSet::OnRep_Ammo(const FGameplayAttributeData& OldAmmo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, Ammo, OldAmmo);
}

void UOceanityAttributeSet::OnRep_MaxAmmo(const FGameplayAttributeData& OldMaxAmmo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, MaxAmmo, OldMaxAmmo);
}

void UOceanityAttributeSet::OnRep_ReloadSpeed(const FGameplayAttributeData& OldReloadSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, ReloadSpeed, OldReloadSpeed);
}

void UOceanityAttributeSet::OnRep_ShootCooldown(const FGameplayAttributeData& OldCooldown)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, ShootCooldown, OldCooldown);
}

void UOceanityAttributeSet::OnRep_MaxSpeed(const FGameplayAttributeData& OldMaxSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, MaxSpeed, OldMaxSpeed);
}

void UOceanityAttributeSet::OnRep_Acceleration(const FGameplayAttributeData& OldAcceleration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, Acceleration, OldAcceleration);
}

void UOceanityAttributeSet::OnRep_TurnSpeed(const FGameplayAttributeData& OldTurnSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, TurnSpeed, OldTurnSpeed);
}

void UOceanityAttributeSet::OnRep_Weight(const FGameplayAttributeData& OldWeight)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, Weight, OldWeight);
}

void UOceanityAttributeSet::OnRep_BackwardsMultiplier(const FGameplayAttributeData& OldBackwardsMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, BackwardsMultiplier, OldBackwardsMultiplier);
}

void UOceanityAttributeSet::OnRep_BoostDuration(const FGameplayAttributeData& OldBoostDuration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, BoostDuration, OldBoostDuration);
}

void UOceanityAttributeSet::OnRep_BoostCooldown(const FGameplayAttributeData& OldBoostCooldown)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, BoostCooldown, OldBoostCooldown);
}

void UOceanityAttributeSet::OnRep_BoostSpeed(const FGameplayAttributeData& OldBoostMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, BoostSpeed, OldBoostMultiplier);
}

void UOceanityAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOceanityAttributeSet, Damage, OldDamage);
}

void UOceanityAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, MaxShield, COND_None, REPNOTIFY_Always);

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, Ammo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, MaxAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, ReloadSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, ShootCooldown, COND_None, REPNOTIFY_Always);

	// Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, MaxSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, Acceleration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, TurnSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, Weight, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, BackwardsMultiplier, COND_None, REPNOTIFY_Always);

	// Boost Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, BoostDuration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, BoostCooldown, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOceanityAttributeSet, BoostSpeed, COND_None, REPNOTIFY_Always);
}

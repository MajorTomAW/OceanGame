// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/OceanityAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "OceanityGameplayTags.h"
#include "Net/UnrealNetwork.h"

UOceanityAttributeSet::UOceanityAttributeSet()
{
	const FOceanityGameplayTags& OceanityTags = FOceanityGameplayTags::Get();
	// Vital Attributes
	TagsToAttributes.Add(OceanityTags.Attributes_Vital_Health, GetHealthAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Vital_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Vital_Shield, GetShieldAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Vital_MaxShield, GetMaxShieldAttribute);

	// Primary Attributes
	TagsToAttributes.Add(OceanityTags.Attributes_Primary_Damage, GetDamageAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Primary_Ammo, GetAmmoAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Primary_MaxAmmo, GetMaxAmmoAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Primary_ReloadSpeed, GetReloadSpeedAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Primary_ShootCooldown, GetShootCooldownAttribute);

	// Secondary Attributes
	TagsToAttributes.Add(OceanityTags.Attributes_Secondary_MaxSpeed, GetMaxSpeedAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Secondary_Acceleration, GetAccelerationAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Secondary_TurnSpeed, GetTurnSpeedAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Secondary_Weight, GetWeightAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Secondary_BackwardsMultiplier, GetBackwardsMultiplierAttribute);

	// Boost Attributes
	TagsToAttributes.Add(OceanityTags.Attributes_Boost_Duration, GetBoostDurationAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Boost_Cooldown, GetBoostCooldownAttribute);
	TagsToAttributes.Add(OceanityTags.Attributes_Boost_Speed, GetBoostSpeedAttribute);
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
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), GetHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetAmmoAttribute())
	{
		SetAmmo(FMath::Clamp(GetAmmo(), 0.0f, GetMaxAmmo()));
	}
	else if (Data.EvaluatedData.Attribute == GetShieldAttribute())
	{
		SetShield(FMath::Clamp(GetShield(), 0.0f, GetMaxShield()));
	}
	else if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		//TODO: Apply damage
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

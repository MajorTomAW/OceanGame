// Copyright © 2023 MajorT. All rights reserved.


#include "CommonAttributeSet.h"

#include "Net/UnrealNetwork.h"

UCommonAttributeSet::UCommonAttributeSet()
{
}

void UCommonAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UCommonAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UCommonAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, Health, OldHealth);
}

void UCommonAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, MaxHealth, OldMaxHealth);
}

void UCommonAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, Shield, OldShield);
}

void UCommonAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldShield)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, MaxShield, OldShield);
}

void UCommonAttributeSet::OnRep_Ammo(const FGameplayAttributeData& OldAmmo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, Ammo, OldAmmo);
}

void UCommonAttributeSet::OnRep_MaxAmmo(const FGameplayAttributeData& OldMaxAmmo)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, MaxAmmo, OldMaxAmmo);
}

void UCommonAttributeSet::OnRep_ReloadSpeed(const FGameplayAttributeData& OldReloadSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, ReloadSpeed, OldReloadSpeed);
}

void UCommonAttributeSet::OnRep_ShootCooldown(const FGameplayAttributeData& OldCooldown)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, ShootCooldown, OldCooldown);
}

void UCommonAttributeSet::OnRep_MaxSpeed(const FGameplayAttributeData& OldMaxSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, MaxSpeed, OldMaxSpeed);
}

void UCommonAttributeSet::OnRep_Acceleration(const FGameplayAttributeData& OldAcceleration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, Acceleration, OldAcceleration);
}

void UCommonAttributeSet::OnRep_TurnSpeed(const FGameplayAttributeData& OldTurnSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, TurnSpeed, OldTurnSpeed);
}

void UCommonAttributeSet::OnRep_Weight(const FGameplayAttributeData& OldWeight)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, Weight, OldWeight);
}

void UCommonAttributeSet::OnRep_BackwardsMultiplier(const FGameplayAttributeData& OldBackwardsMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, BackwardsMultiplier, OldBackwardsMultiplier);
}

void UCommonAttributeSet::OnRep_BoostDuration(const FGameplayAttributeData& OldBoostDuration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, BoostDuration, OldBoostDuration);
}

void UCommonAttributeSet::OnRep_BoostCooldown(const FGameplayAttributeData& OldBoostCooldown)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, BoostCooldown, OldBoostCooldown);
}

void UCommonAttributeSet::OnRep_BoostSpeed(const FGameplayAttributeData& OldBoostMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, BoostSpeed, OldBoostMultiplier);
}

void UCommonAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCommonAttributeSet, Damage, OldDamage);
}

void UCommonAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, MaxShield, COND_None, REPNOTIFY_Always);

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, Ammo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, MaxAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, ReloadSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, ShootCooldown, COND_None, REPNOTIFY_Always);

	// Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, MaxSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, Acceleration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, TurnSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, Weight, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, BackwardsMultiplier, COND_None, REPNOTIFY_Always);

	// Boost Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, BoostDuration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, BoostCooldown, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommonAttributeSet, BoostSpeed, COND_None, REPNOTIFY_Always);
	
}
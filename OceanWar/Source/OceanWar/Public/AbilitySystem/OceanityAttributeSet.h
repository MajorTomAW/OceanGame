// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CommonAttributeSet.h"
#include "OceanityAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UOceanityAttributeSet : public UCommonAttributeSet
{
	GENERATED_BODY()

public:
	UOceanityAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	/*
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Shield, Category = "Vital")
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, Shield)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxShield, Category = "Vital")
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, MaxShield)

	/*
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Damage, Category = "Primary")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Ammo, Category = "Primary")
	FGameplayAttributeData Ammo;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, Ammo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxAmmo, Category = "Primary")
	FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, MaxAmmo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ReloadSpeed, Category = "Primary")
	FGameplayAttributeData ReloadSpeed;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, ReloadSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ShootCooldown, Category = "Primary")
	FGameplayAttributeData ShootCooldown;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, ShootCooldown)

	/*
	 * Secondary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxSpeed, Category = "Secondary")
	FGameplayAttributeData MaxSpeed;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, MaxSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Acceleration, Category = "Secondary")
	FGameplayAttributeData Acceleration;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, Acceleration)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TurnSpeed, Category = "Secondary")
	FGameplayAttributeData TurnSpeed;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, TurnSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Weight, Category = "Secondary")
	FGameplayAttributeData Weight;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, Weight)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BackwardsMultiplier, Category = "Secondary")
	FGameplayAttributeData BackwardsMultiplier;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, BackwardsMultiplier)

	/*
	 * Boost Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BoostDuration, Category = "Boost")
	FGameplayAttributeData BoostDuration;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, BoostDuration)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BoostCooldown, Category = "Boost")
	FGameplayAttributeData BoostCooldown;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, BoostCooldown)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BoostSpeed, Category = "Boost")
	FGameplayAttributeData BoostSpeed;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, BoostSpeed)

	/*
	 * Meta Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, IncomingDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingCoins;
	ATTRIBUTE_ACCESSORS(UOceanityAttributeSet, IncomingCoins)

	/** Replication */
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldShield);

	UFUNCTION()
	virtual void OnRep_MaxShield(const FGameplayAttributeData& OldShield);

	UFUNCTION()
	virtual void OnRep_Ammo(const FGameplayAttributeData& OldAmmo);

	UFUNCTION()
	virtual void OnRep_MaxAmmo(const FGameplayAttributeData& OldMaxAmmo);

	UFUNCTION()
	virtual void OnRep_ReloadSpeed(const FGameplayAttributeData& OldReloadSpeed);

	UFUNCTION()
	virtual void OnRep_ShootCooldown(const FGameplayAttributeData& OldCooldown);

	UFUNCTION()
	virtual void OnRep_MaxSpeed(const FGameplayAttributeData& OldMaxSpeed);

	UFUNCTION()
	virtual void OnRep_Acceleration(const FGameplayAttributeData& OldAcceleration);

	UFUNCTION()
	virtual void OnRep_TurnSpeed(const FGameplayAttributeData& OldTurnSpeed);

	UFUNCTION()
	virtual void OnRep_Weight(const FGameplayAttributeData& OldWeight);

	UFUNCTION()
	virtual void OnRep_BackwardsMultiplier(const FGameplayAttributeData& OldBackwardsMultiplier);

	UFUNCTION()
	virtual void OnRep_BoostDuration(const FGameplayAttributeData& OldBoostDuration);

	UFUNCTION()
	virtual void OnRep_BoostCooldown(const FGameplayAttributeData& OldBoostCooldown);

	UFUNCTION()
	virtual void OnRep_BoostSpeed(const FGameplayAttributeData& OldBoostMultiplier);

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldDamage);
};

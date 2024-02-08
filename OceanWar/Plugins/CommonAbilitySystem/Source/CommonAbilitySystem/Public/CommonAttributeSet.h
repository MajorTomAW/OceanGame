// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CommonAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FGameplayTag;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class COMMONABILITYSYSTEM_API UCommonAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCommonAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/*
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Shield, Category = "Vital")
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, Shield)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxShield, Category = "Vital")
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, MaxShield)

	/*
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Damage, Category = "Primary")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Ammo, Category = "Primary")
	FGameplayAttributeData Ammo;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, Ammo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxAmmo, Category = "Primary")
	FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, MaxAmmo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ReloadSpeed, Category = "Primary")
	FGameplayAttributeData ReloadSpeed;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, ReloadSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ShootCooldown, Category = "Primary")
	FGameplayAttributeData ShootCooldown;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, ShootCooldown)

	/*
	 * Secondary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxSpeed, Category = "Secondary")
	FGameplayAttributeData MaxSpeed;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, MaxSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Acceleration, Category = "Secondary")
	FGameplayAttributeData Acceleration;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, Acceleration)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TurnSpeed, Category = "Secondary")
	FGameplayAttributeData TurnSpeed;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, TurnSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Weight, Category = "Secondary")
	FGameplayAttributeData Weight;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, Weight)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BackwardsMultiplier, Category = "Secondary")
	FGameplayAttributeData BackwardsMultiplier;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, BackwardsMultiplier)

	/*
	 * Boost Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BoostDuration, Category = "Boost")
	FGameplayAttributeData BoostDuration;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, BoostDuration)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BoostCooldown, Category = "Boost")
	FGameplayAttributeData BoostCooldown;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, BoostCooldown)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BoostSpeed, Category = "Boost")
	FGameplayAttributeData BoostSpeed;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, BoostSpeed)

	/*
	 * Meta Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UCommonAttributeSet, IncomingDamage)

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

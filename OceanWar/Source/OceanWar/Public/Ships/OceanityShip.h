// Copyright © 2023 MajorT. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "OceanityShip.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAnimMontage;
class UAbilitySystemComponent;

UCLASS(Abstract)
class OCEANWAR_API AOceanityShip : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AOceanityShip();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void InitializeAttributes() const;
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "OceanityShip|Combat")
	bool bHitReacting = false;

	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_HandleDeath();
	

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAO_Yaw() const {return AO_Yaw ;}

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAO_Pitch() const {return AO_Pitch ;}
	
protected:
	/** Ability System */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();
	virtual void Tick(float DeltaSeconds) override;
	void AddStartupGameplayAbilities();

	/** Components */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponSocketMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> EngineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCapsuleComponent> ShipHitbox;

	/** Player data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OceanityShip|Combat")
	FName WeaponTipSockedName = "WeaponTipSocket";

	void InitializeSpecificAttribute(TSubclassOf<UGameplayEffect> InGameplayEffect, float Level) const;

	UPROPERTY(EditDefaultsOnly, Category = "OceanityShip|Animations")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
	/** Aiming */
	float AO_Yaw;
	float AO_Pitch;
	void AimOffset(float DeltaTime);

	UPROPERTY()
	TObjectPtr<AActor> CombatTarget;

private:
	UPROPERTY(EditDefaultsOnly, Category = "OceanityShip|Material")
	TObjectPtr<UMaterialInterface> HullMaterialInstance;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicHullMaterialInstance;
};

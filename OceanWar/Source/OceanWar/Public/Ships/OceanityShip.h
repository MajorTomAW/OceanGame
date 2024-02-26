// Copyright © 2023 MajorT. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Equipment/Components/OceanityEquipmentComponent.h"
#include "Interfaces/CombatInterface.h"
#include "OceanityShip.generated.h"

class UOceanityEquipmentComponent;
enum class EEngineClassType : uint8;
enum class ETurretClassType : uint8;
enum class EHullClassType : uint8;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAnimMontage;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityActorInfoSetSignature);

UCLASS(Abstract)
class OCEANWAR_API AOceanityShip : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AOceanityShip();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	UOceanityEquipmentComponent* GetEquipmentComponent() const { return EquipmentComponent; }
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "OceanityShip|Combat")
	bool bHitReacting = false;

	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_HandleDeath();
	

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAO_Yaw() const {return AO_Yaw ;}

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAO_Pitch() const {return AO_Pitch ;}

	/** ICombatInterface */
	virtual FVector GetCombatSocketLocation() const override
	{
		return WeaponMesh->GetSocketLocation(EquipmentComponent->GetAttackSocket());
	};
	virtual USkeletalMeshComponent* GetWeaponMesh() const override
	{
		return WeaponMesh;
	}
	virtual UAnimMontage* GetWeaponMontage() const override;
	/** End ICombatInterface */

	UPROPERTY(BlueprintAssignable)
	FOnAbilityActorInfoSetSignature OnAbilityActorInfoSetDelegate;
	
protected:
	/** Ability System */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UOceanityEquipmentComponent> EquipmentComponent;

	virtual void InitAbilityActorInfo();
	virtual void AbilityActorInfoSet();
	virtual void Tick(float DeltaSeconds) override;

	/** Components */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponSocketMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> EngineMesh;

	/** Ship Classes */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OceanityShip")
	EHullClassType HullClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OceanityShip")
	ETurretClassType TurretClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OceanityShip")
	EEngineClassType EngineClass;

	void InitializeSpecificAttribute(TSubclassOf<UGameplayEffect> InGameplayEffect, float Level) const;

	UPROPERTY(EditDefaultsOnly, Category = "OceanityShip|Animations")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
	/** Aiming */
	float AO_Yaw;
	float AO_Pitch;
	void AimOffset(float DeltaTime);

	UPROPERTY()
	TObjectPtr<AActor> CombatTarget;

	/** Delegates */
	UFUNCTION()
	void OnTurretMeshChanged(USkeletalMesh* NewMesh);

	UFUNCTION()
	void OnEngineMeshChanged(USkeletalMesh* NewMesh);

	UFUNCTION()
	void OnHullMeshChanged(USkeletalMesh* NewMesh);
	void BindFunctionsToEquipmentComponent();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "OceanityShip|Material")
	TObjectPtr<UMaterialInterface> HullMaterialInstance;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicHullMaterialInstance;
};

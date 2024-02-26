// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/Ship/ShipClassInfo.h"
#include "AbilitySystem/Data/Ship/Mesh/ShipMeshInfo.h"
#include "Components/ActorComponent.h"
#include "OceanityEquipmentComponent.generated.h"

class AEngineEquipment;
class ATurretEquipment;
struct FShipClassDefaultInfo;
enum class EHullClassType : uint8;
enum class EEngineClassType : uint8;
enum class ETurretClassType : uint8;
class UHullClassInfo;
class UEngineClassInfo;
class UTurretClassInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentMeshChangedSignature, USkeletalMesh*, NewMesh);

UCLASS(ClassGroup=(Equipment), meta=(BlueprintSpawnableComponent))
class OCEANWAR_API UOceanityEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOceanityEquipmentComponent();

	template<class UserClass, typename TurretFuncType, typename EngineFuncType, typename HullFuncType>
	void BindEquipmentActions(UserClass* Object, TurretFuncType TurretFunc, EngineFuncType EngineFunc, HullFuncType HullFunc);
	
	void InitActorEquipment(ETurretClassType InTurretClassType, EEngineClassType InEngineClassType, EHullClassType InHullClassType);

	static UOceanityEquipmentComponent* FindEquipmentComponent(const AActor* Actor);
	
	/*
	 *Turret Info Getter
	 */
	UFUNCTION(BlueprintPure, Category = "Equipment")
	FORCEINLINE FName GetAttackSocket() const { return TurretInfo.MeshInfoAsset->AttackSocket; }

	UFUNCTION(BlueprintPure, Category = "Equipment")
	FORCEINLINE UAnimMontage* GetAttackMontage() const { return TurretInfo.MeshInfoAsset->AttackMontage; }

	/*
	 * Data Assets
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<UTurretClassInfo> TurretDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<UEngineClassInfo> EngineDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<UHullClassInfo> HullDataAsset;
	
	
	UPROPERTY()
	FShipClassDefaultInfo TurretInfo;

	UPROPERTY()
	FShipClassDefaultInfo EngineInfo;

	UPROPERTY()
	FShipClassDefaultInfo HullInfo;
	
	/*
	 * Delegates
	 */
	UPROPERTY(BlueprintAssignable)
	FOnEquipmentMeshChangedSignature OnTurretMeshChanged;

	UPROPERTY(BlueprintAssignable)
	FOnEquipmentMeshChangedSignature OnEngineMeshChanged;

	UPROPERTY(BlueprintAssignable)
	FOnEquipmentMeshChangedSignature OnHullMeshChanged;

private:
	bool bInitialized = false;
};

template <class UserClass, typename TurretFuncType, typename EngineFuncType, typename HullFuncType>
void UOceanityEquipmentComponent::BindEquipmentActions(UserClass* Object, TurretFuncType TurretFunc,
	EngineFuncType EngineFunc, HullFuncType HullFunc)
{
	OnTurretMeshChanged.AddDynamic(Object, TurretFunc);
	OnEngineMeshChanged.AddDynamic(Object, EngineFunc);
	OnHullMeshChanged.AddDynamic(Object, HullFunc);
}

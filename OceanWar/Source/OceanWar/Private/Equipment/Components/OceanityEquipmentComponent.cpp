// Copyright © 2024 MajorT. All rights reserved.


#include "Equipment/Components/OceanityEquipmentComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Data/Ship/EngineClassInfo.h"
#include "AbilitySystem/Data/Ship/HullClassInfo.h"
#include "AbilitySystem/Data/Ship/TurretClassInfo.h"
#include "AbilitySystem/FunctionLibraries/OceanityAbilityFunctionLibrary.h"



UOceanityEquipmentComponent::UOceanityEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UOceanityEquipmentComponent::InitActorEquipment(ETurretClassType InTurretClassType, EEngineClassType InEngineClassType, EHullClassType InHullClassType)
{
	TurretInfo = TurretDataAsset->GetTurretClassDefaults(InTurretClassType);
	EngineInfo = EngineDataAsset->GetEngineClassDefaults(InEngineClassType);
	HullInfo = HullDataAsset->GetHullClassDefaults(InHullClassType);

	checkf(TurretInfo.MeshInfoAsset && EngineInfo.MeshInfoAsset && HullInfo.MeshInfoAsset, TEXT("MeshInfoAsset is not set in Turret, Engine or Hull Class Defaults"));
	OnTurretMeshChanged.Broadcast(TurretInfo.MeshInfoAsset->SkeletalMesh);
	OnEngineMeshChanged.Broadcast(EngineInfo.MeshInfoAsset->SkeletalMesh);
	OnHullMeshChanged.Broadcast(HullInfo.MeshInfoAsset->SkeletalMesh);
	
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))
	{
		UOceanityAbilityFunctionLibrary::AddStartupAbilities(GetOwner(), InTurretClassType, InEngineClassType, InHullClassType, ASC);
		UOceanityAbilityFunctionLibrary::InitializeDefaultAttribute(GetOwner(), InTurretClassType, InEngineClassType, InHullClassType, ASC);
	}
}

UOceanityEquipmentComponent* UOceanityEquipmentComponent::FindEquipmentComponent(const AActor* Actor)
{
	if (Actor == nullptr)
	{
		return nullptr;
	}
	return Actor->FindComponentByClass<UOceanityEquipmentComponent>();
}


// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ShipMeshInfo.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UShipMeshInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShipMeshInfo")
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponMeshInfo")
	bool bIsWeapon = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponMeshInfo", meta =(EditCondition = "bIsWeapon"))
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponMeshInfo", meta =(EditCondition = "bIsWeapon"))
	FName AttackSocket = FName("WeaponTipSocket");
};

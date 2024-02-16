// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ShipClassInfo.generated.h"


USTRUCT(BlueprintType)
struct FShipClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UShipMeshInfo> MeshInfoAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UShipAbilitySetInfo> AbilitySetAsset;
};
/**
 * Base class for ship data assets.
 * All ship data assets should inherit from this class.
 * Used to initialize the ship attributes and abilities.
 */
UCLASS(Abstract)
class OCEANWAR_API UShipClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<class UGameplayAbility>> CommonAbilities;
};

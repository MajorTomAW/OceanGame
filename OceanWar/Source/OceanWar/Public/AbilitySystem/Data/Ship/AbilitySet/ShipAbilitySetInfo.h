// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ShipAbilitySetInfo.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UShipAbilitySetInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Attribute"))
	TMap<UPARAM(meta = (Categories = "Attribute")) FGameplayTag, float> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Attribute"))
	TMap<UPARAM(meta = (Categories = "Attribute")) FGameplayTag, float> DefaultDerivedAttributes;
};

// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInputInfo.generated.h"

USTRUCT(BlueprintType)
struct FOceanityAbilityInputInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (Categories = "Input.InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName InputKeyName = FName("None");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "Should show input key"))
	bool bHas_InputKey = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "Should show input icon"))
	bool bHas_InputIcon = false;
};

/**
 * 
 */
UCLASS()
class OCEANWAR_API UAbilityInputInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Input Info")
	TArray<FOceanityAbilityInputInfo> InputInfos;

	FOceanityAbilityInputInfo FindAbilityInputInfoByTag(const FGameplayTag& Tag, bool bLogNotFound = true) const;
};

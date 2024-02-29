// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInputInfo.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInfo.generated.h"

USTRUCT(BlueprintType)
struct FOceanityAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Ability.Descriptor"))
	FGameplayTag AbilityTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> AbilityIcon = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FOceanityAbilityInputInfo InputInfo = FOceanityAbilityInputInfo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bShouldShowInUI = true;
};

/**
 * 
 */
UCLASS()
class OCEANWAR_API UAbilityInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Info")
	TArray<FOceanityAbilityInfo> AbilityInfos;

	FOceanityAbilityInfo FindAbilityInfoByTag(const FGameplayTag& Tag, bool bLogNotFound = true) const;
};

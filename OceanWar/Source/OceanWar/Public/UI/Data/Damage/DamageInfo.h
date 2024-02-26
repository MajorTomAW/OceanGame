// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DamageInfo.generated.h"

USTRUCT(BlueprintType)
struct FUIDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DamageInfo")
	FGameplayTag DamageTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DamageInfo")
	TObjectPtr<UTexture2D> DamageIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DamageInfo")
	FLinearColor IconColor = FLinearColor::White;
};

/**
 * Data asset for damage information
 * Stores information about damage based on gameplay tags, their damage icon and value
 */
UCLASS()
class OCEANWAR_API UDamageInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DamageInfo")
	TArray<FUIDamageInfo> DamageInfo;

	UFUNCTION(BlueprintCallable)
	static void GetUIDamageInfoFromTag(UDamageInfo* DataAsset, const FGameplayTag& Tag, bool& bFound, FUIDamageInfo& OutInfo);
};

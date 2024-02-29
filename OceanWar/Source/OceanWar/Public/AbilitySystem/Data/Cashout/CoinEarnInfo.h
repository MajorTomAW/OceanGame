// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CoinEarnInfo.generated.h"


USTRUCT(BlueprintType)
struct FCoinEarnInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Damage.Event.Hit"))
	FGameplayTag DamageTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CoinsEarned = 0;
};

/**
 * 
 */
UCLASS()
class OCEANWAR_API UCoinEarnInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Coin Info")
	TArray<FCoinEarnInfoStruct> CoinEarnInfos;

	int32 GetCoinsEarned(const FGameplayTagContainer& DamageTags) const;
};

// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

struct FGameplayTag;

USTRUCT(BlueprintType)
struct FOceanityAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float DefaultValue = 0.0f;
};

/**
 * AttributeInfo is a data asset that contains the default data for an attribute.
 * Including the name, description, and default value, etc.
 */
UCLASS()
class OCEANWAR_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FOceanityAttributeInfo FindAttributeInfoForTag(const FGameplayTag& InTag, bool bLogNotFound) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FOceanityAttributeInfo> AttributeInfos;
};

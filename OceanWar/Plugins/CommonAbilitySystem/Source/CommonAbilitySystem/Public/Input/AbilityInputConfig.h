// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FCommonInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "Input.InputTag"))
	FGameplayTag AbilityTag = FGameplayTag::EmptyTag;
};

/**
 * Input configuration data asset for abilities
 * Stores an array of input bindings for an ability with a gameplay tag
 */
UCLASS()
class COMMONABILITYSYSTEM_API UAbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* GetInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FCommonInputAction> InputActions;
};

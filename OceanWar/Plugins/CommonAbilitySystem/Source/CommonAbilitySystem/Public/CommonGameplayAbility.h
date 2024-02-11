// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CommonGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class COMMONABILITYSYSTEM_API UCommonGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (Categories = "Input.InputTag"))
	FGameplayTag StartupInputTag;
};

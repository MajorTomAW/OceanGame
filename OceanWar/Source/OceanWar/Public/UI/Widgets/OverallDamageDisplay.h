// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverallDamageDisplay.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UOverallDamageDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void DisplayDamage(float DamageAmount, FGameplayTagContainer DamageTags);
};

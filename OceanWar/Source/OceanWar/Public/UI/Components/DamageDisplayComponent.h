// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/WidgetComponent.h"
#include "DamageDisplayComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OCEANWAR_API UDamageDisplayComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UDamageDisplayComponent();

	UFUNCTION(BlueprintCallable)
	void DisplayDamage(float DamageAmount, FGameplayTagContainer DamageTags) const;
};

// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonAbilityComponent.h"
#include "OceanityAbilityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OCEANWAR_API UOceanityAbilityComponent : public UCommonAbilityComponent
{
	GENERATED_BODY()

public:
	UOceanityAbilityComponent();

	void AddStartupGameplayAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	bool bStartupAbilitiesGiven = false;
};

// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonAbilityComponent.h"
#include "OceanityAbilityComponent.generated.h"

class UOceanityAbilityComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGivenSignature, UOceanityAbilityComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbilitySignature, const FGameplayAbilitySpec&);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OCEANWAR_API UOceanityAbilityComponent : public UCommonAbilityComponent
{
	GENERATED_BODY()

public:
	UOceanityAbilityComponent();

	virtual void BeginPlay() override;
	virtual void OnRep_ActivateAbilities() override;

	void AddStartupGameplayAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ForEachAbility(const FForEachAbilitySignature& Delegate);

	bool bStartupAbilitiesGiven = false;

	FAbilitiesGivenSignature OnAbilitiesGivenDelegate;
};

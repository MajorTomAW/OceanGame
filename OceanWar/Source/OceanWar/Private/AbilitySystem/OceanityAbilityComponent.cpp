// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/OceanityAbilityComponent.h"

#include "CommonGameplayAbility.h"

UOceanityAbilityComponent::UOceanityAbilityComponent()
{
}

void UOceanityAbilityComponent::AddStartupGameplayAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		if (const UCommonGameplayAbility* OceanityAbility = Cast<UCommonGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(OceanityAbility->StartupInputTag);	
		}
		GiveAbility(AbilitySpec);
		bStartupAbilitiesGiven = true;
	}
}

void UOceanityAbilityComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpec.Ability->InputPressed(AbilitySpec.Handle, AbilityActorInfo.Get(), AbilitySpec.ActivationInfo);
			if (!AbilitySpec.IsActive())
				TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UOceanityAbilityComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpec.Ability->InputReleased(AbilitySpec.Handle, AbilityActorInfo.Get(), AbilitySpec.ActivationInfo);;
		}
	}
}

// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/OceanityAbilityComponent.h"

#include "CommonGameplayAbility.h"
#include "Log/OceanityLogChannels.h"

UOceanityAbilityComponent::UOceanityAbilityComponent()
{
}

void UOceanityAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UOceanityAbilityComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	if (!bStartupAbilitiesGiven)
	{
		bStartupAbilitiesGiven = true;
		OnAbilitiesGivenDelegate.Broadcast(this);
	}
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
	}

	bStartupAbilitiesGiven = true;
	OnAbilitiesGivenDelegate.Broadcast(this);
}

void UOceanityAbilityComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
				AbilitySpec.Ability->InputPressed(AbilitySpec.Handle, AbilityActorInfo.Get(), AbilitySpec.ActivationInfo);
			}
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

void UOceanityAbilityComponent::ForEachAbility(const FForEachAbilitySignature& Delegate)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogOceanityGAS, Error, TEXT("Failed to execute delegate for ability %s"), *AbilitySpec.Ability->GetName());
		}
	}
}

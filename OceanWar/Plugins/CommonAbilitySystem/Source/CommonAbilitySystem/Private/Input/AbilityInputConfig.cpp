// Copyright © 2024 MajorT. All rights reserved.


#include "Input/AbilityInputConfig.h"

#include "CommonAbilitySystem.h"

const UInputAction* UAbilityInputConfig::GetInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FCommonInputAction& Action : InputActions)
	{
		if (Action.AbilityTag.MatchesTagExact(InputTag) && Action.InputAction)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound) UE_LOG(CommonAbilityLog, Error, TEXT("No input action found for tag %s"), *InputTag.ToString());
	return nullptr;
}

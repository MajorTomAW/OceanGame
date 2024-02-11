// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/AbilityInputConfig.h"
#include "OceanityInputComponent.generated.h"


UCLASS(ClassGroup=(Input), meta=(BlueprintSpawnableComponent))
class OCEANWAR_API UOceanityInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAbilityInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UOceanityInputComponent::BindAbilityActions(const UAbilityInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	checkf(InputConfig, TEXT("InputConfig is null"));

	for (const FCommonInputAction& Action : InputConfig->InputActions)
	{
		if (Action.InputAction && Action.AbilityTag.IsValid())
		{
			if (PressedFunc)
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.AbilityTag);

			if (ReleasedFunc)
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.AbilityTag);

			if (HeldFunc)
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.AbilityTag);
		}
	}
}

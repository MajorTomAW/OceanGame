// Copyright © 2023 MajorT. All rights reserved.


#include "Controller/CommonWidgetController.h"

void UCommonWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InParams)
{
	PlayerController = InParams.PlayerController;
	PlayerState = InParams.PlayerState;
	AbilitySystemComponent = InParams.AbilitySystemComponent;
	AttributeSet = InParams.AttributeSet;
}

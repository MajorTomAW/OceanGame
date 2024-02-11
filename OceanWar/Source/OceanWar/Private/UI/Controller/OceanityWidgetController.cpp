// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Controller/OceanityWidgetController.h"

void UOceanityWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InParams)
{
	PlayerController = InParams.PlayerController;
	PlayerState = InParams.PlayerState;
	AbilitySystemComponent = InParams.AbilitySystemComponent;
	AttributeSet = InParams.AttributeSet;
}

void UOceanityWidgetController::BroadcastInitialValues()
{
}

void UOceanityWidgetController::BindCallbacksToDependencies()
{
}

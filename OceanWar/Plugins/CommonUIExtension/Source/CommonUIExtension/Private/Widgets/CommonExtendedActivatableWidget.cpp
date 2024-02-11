// Copyright © 2023 MajorT. All rights reserved.


#include "Widgets/CommonExtendedActivatableWidget.h"

void UCommonExtendedActivatableWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	if (IsValid(InWidgetController))
	WidgetControllerSet(InWidgetController);
}

void UCommonExtendedActivatableWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	switch (InputMode)
	{
	case EInputMode::Game:
		GetOwningPlayer()->SetShowMouseCursor(false);
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		break;
	case EInputMode::All:
		GetOwningPlayer()->SetShowMouseCursor(true);
		GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
		break;
	case EInputMode::Menu:
		GetOwningPlayer()->SetShowMouseCursor(true);
		GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
		break;
	}
}



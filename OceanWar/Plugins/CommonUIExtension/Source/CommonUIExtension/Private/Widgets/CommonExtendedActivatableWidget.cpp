// Copyright © 2023 MajorT. All rights reserved.


#include "Widgets/CommonExtendedActivatableWidget.h"

void UCommonExtendedActivatableWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	if (IsValid(InWidgetController))
	OnWidgetControllerSet(WidgetController);
}

void UCommonExtendedActivatableWidget::OnWidgetControllerSet(UObject* InWidgetController)
{
	WidgetControllerSet_BP(InWidgetController);
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



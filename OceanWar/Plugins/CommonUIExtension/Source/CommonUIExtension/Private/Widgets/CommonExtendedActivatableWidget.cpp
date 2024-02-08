// Copyright © 2023 MajorT. All rights reserved.


#include "Widgets/CommonExtendedActivatableWidget.h"

void UCommonExtendedActivatableWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	if (IsValid(InWidgetController))
	WidgetControllerSet(InWidgetController);
}

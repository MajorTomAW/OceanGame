// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Widgets/OverallEntityProgressBar.h"

#include "Ships/AIShip.h"

void UOverallEntityProgressBar::BindToRespondingAttributes()
{
	if (AAIShip* AIShip = Cast<AAIShip>(WidgetController))
	{
		AIShip->OnAttributeValueChangedDelegate.AddDynamic(this, &ThisClass::AttributeValueChanged);
	}
}

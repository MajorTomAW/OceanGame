// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Widgets/AttributeDelegateWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UI/Controller/AttributeWidgetController.h"

void UAttributeDelegateWidget::OnWidgetControllerSet(UObject* InWidgetController)
{
	Super::OnWidgetControllerSet(InWidgetController);
	BindToRespondingAttributes();
}

void UAttributeDelegateWidget::BindToRespondingAttributes()
{
	if (UAttributeWidgetController* AttributeWC = Cast<UAttributeWidgetController>(WidgetController))
	{
		AttributeWC->OnAttributeValueChangedDelegate.AddDynamic(this, &ThisClass::AttributeValueChanged);
	}
}

void UAttributeDelegateWidget::AttributeValueChanged(const FGameplayTag& AttributeTag, float NewValue)
{
	if (AttributeTag.MatchesTagExact(PrimaryAttributeTag) && bBindToPrimaryAttribute)
	{
		PrimaryAttributeValueChanged(NewValue);
	}
	if (AttributeTag.MatchesTagExact(SecondaryAttributeTag) && bBindToSecondaryAttribute)
	{
		SecondaryAttributeValueChanged(NewValue);
	}
}

void UAttributeDelegateWidget::PrimaryAttributeValueChanged(float NewValue)
{
}

void UAttributeDelegateWidget::SecondaryAttributeValueChanged(float NewValue)
{
}

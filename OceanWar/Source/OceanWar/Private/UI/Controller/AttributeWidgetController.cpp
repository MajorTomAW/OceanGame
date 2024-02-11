// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Controller/AttributeWidgetController.h"

#include "CommonAttributeSet.h"

void UAttributeWidgetController::BroadcastInitialValues()
{
	UCommonAttributeSet* AS = Cast<UCommonAttributeSet>(this->AttributeSet);
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());		
	}
}

void UAttributeWidgetController::BindCallbacksToDependencies()
{
	UCommonAttributeSet* AS = Cast<UCommonAttributeSet>(this->AttributeSet);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			});
	}
}

void UAttributeWidgetController::BroadcastAttributeInfo(const FGameplayTag& Tag, const FGameplayAttribute& Attribute) const
{
	OnAttributeValueChangedDelegate.Broadcast(Tag, Attribute.GetNumericValue(AttributeSet));
}

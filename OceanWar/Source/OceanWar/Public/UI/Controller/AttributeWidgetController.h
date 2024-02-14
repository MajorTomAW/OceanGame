// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "OceanityWidgetController.h"
#include "AttributeWidgetController.generated.h"

struct FGameplayAttribute;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FValueChangedSignature, const FGameplayTag&, Tag, float, NewValue);

/**
 * Widget controller for attribute widgets.
 * Used to bind attribute values to the widget and broadcast changes.
 */
UCLASS(Blueprintable, BlueprintType)
class OCEANWAR_API UAttributeWidgetController : public UOceanityWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FValueChangedSignature OnAttributeValueChangedDelegate;

private:
	void BroadcastAttributeInfo(const FGameplayTag& Tag, const FGameplayAttribute& Attribute) const;
	
};

// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Widgets/CommonExtendedActivatableWidget.h"
#include "AttributeDelegateWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChangedDelegate, float, NewValue);

/**
 * Widget that binds to responding attributes 
 */
UCLASS(Abstract)
class OCEANWAR_API UAttributeDelegateWidget : public UCommonExtendedActivatableWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (EditCondition = "bBindToPrimaryAttribute", Categories = "Attribute"))
	FGameplayTag PrimaryAttributeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (EditCondition = "bBindToSecondaryAttribute", Categories = "Attribute"))
	FGameplayTag SecondaryAttributeTag;

	UPROPERTY(EditAnywhere, Category = "Attributes", meta = (InlineEditConditionToggle))
	bool bBindToPrimaryAttribute = false;

	UPROPERTY(EditAnywhere, Category = "Attributes", meta = (InlineEditConditionToggle))
	bool bBindToSecondaryAttribute = false;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChangedDelegate OnPrimaryAttributeValueChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChangedDelegate OnSecondaryAttributeValueChanged;

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Primary Attribute Value Changed")
	void PrimaryAttributeValueChanged_BP(float NewValue);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Secondary Attribute Value Changed")
	void SecondaryAttributeValueChanged_BP(float NewValue);

protected:
	virtual void OnWidgetControllerSet(UObject* InWidgetController) override;
	virtual void BindToRespondingAttributes();

	UFUNCTION(BlueprintCallable)
	virtual void PrimaryAttributeValueChanged(float NewValue);

	UFUNCTION(BlueprintCallable)
	virtual void SecondaryAttributeValueChanged(float NewValue);

	UFUNCTION()
	virtual void AttributeValueChanged(const FGameplayTag& AttributeTag, float NewValue);
};

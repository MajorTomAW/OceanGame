// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "OceanityWidgetController.h"
#include "UI/Data/Attributes/AttributeInfo.h"
#include "ShipCustomizationWidgetController.generated.h"


struct FOceanityAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedComponentChanged, TArray<FOceanityAttributeInfo>, AttributeInfos);

class UAttributeInfo;
/**
 * Widget controller for the ship customization widget
 * Used to handle the ship customization widget
 */
UCLASS()
class OCEANWAR_API UShipCustomizationWidgetController : public UOceanityWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnSelectedComponentChanged OnSelectedComponentChangedDelegate;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI Data")
	TObjectPtr<UAttributeInfo> AttributeInfo;
};

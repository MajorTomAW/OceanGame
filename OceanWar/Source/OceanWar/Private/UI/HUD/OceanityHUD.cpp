// Copyright © 2024 MajorT. All rights reserved.


#include "UI/HUD/OceanityHUD.h"
#include "UI/Controller/AttributeWidgetController.h"
#include "UI/Controller/ShipCustomizationWidgetController.h"
#include "Widgets/CommonPrimaryGameLayout.h"

UAttributeWidgetController* AOceanityHUD::GetAttributeWidgetController(const FWidgetControllerParams& Params)
{
	if (!IsValid(AttributeWidgetController))
	{
		AttributeWidgetController = NewObject<UAttributeWidgetController>(this, AttributeWidgetControllerClass);
		AttributeWidgetController->SetWidgetControllerParams(Params);
	}
	return AttributeWidgetController;
}

UShipCustomizationWidgetController* AOceanityHUD::GetShipCustomizationWidgetController(
	const FWidgetControllerParams& Params)
{
	if (!IsValid(ShipCustomizationWidgetController))
	{
		ShipCustomizationWidgetController = NewObject<UShipCustomizationWidgetController>(this,ShipCustomizationWidgetControllerClass);
		ShipCustomizationWidgetController->SetWidgetControllerParams(Params);
	}
	return ShipCustomizationWidgetController;
}

void AOceanityHUD::InitOverlayWithParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(AttributeWidgetControllerClass, TEXT("AttributeWidgetControllerClass is not set in %s"), *GetName());
	checkf(ShipCustomizationWidgetControllerClass, TEXT("ShipCustomizationWidgetControllerClass is not set in %s"), *GetName());

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UAttributeWidgetController* WidgetController = GetAttributeWidgetController(WidgetControllerParams);

	if (OverallUILayoutWidget)
	{
		OverallUILayoutWidget->SetWidgetController(WidgetController);
	}
}

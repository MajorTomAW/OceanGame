// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "HUD/CommonHUD.h"
#include "UI/Controller/OceanityWidgetController.h"
#include "OceanityHUD.generated.h"

class UShipCustomizationWidgetController;
class UOceanityWidgetController;
class UAttributeWidgetController;
/**
 * 
 */
UCLASS()
class OCEANWAR_API AOceanityHUD : public ACommonHUD
{
	GENERATED_BODY()

public:
	UAttributeWidgetController* GetAttributeWidgetController(const FWidgetControllerParams& Params);
	UShipCustomizationWidgetController* GetShipCustomizationWidgetController(const FWidgetControllerParams& Params);
	
	void InitOverlayWithParams(APlayerController* PC, APlayerState* PS, class UAbilitySystemComponent* ASC, class UAttributeSet* AS);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Controllers")
	TSubclassOf<UAttributeWidgetController> AttributeWidgetControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Controllers")
	TSubclassOf<UShipCustomizationWidgetController> ShipCustomizationWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UAttributeWidgetController> AttributeWidgetController;

	UPROPERTY()
	TObjectPtr<UShipCustomizationWidgetController> ShipCustomizationWidgetController;
};

// Copyright © 2023 MajorT. All rights reserved.


#include "HUD/CommonHUD.h"

#include "Blueprint/UserWidget.h"
#include "Controller/AttributeWidgetController.h"
#include "Widgets/CommonExtendedActivatableWidget.h"
#include "Widgets/CommonPrimaryGameLayout.h"

UAttributeWidgetController* ACommonHUD::GetAttributeWidgetController(const FWidgetControllerParams& Params)
{
	if (!IsValid(AttributeWidgetController))
	{
		AttributeWidgetController = NewObject<UAttributeWidgetController>(this, AttributeWidgetControllerClass);
		AttributeWidgetController->SetWidgetControllerParams(Params);
	}
	return AttributeWidgetController;
}

void ACommonHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
	UAttributeSet* AS)
{
	checkf(OverallUILayoutWidgetClass, TEXT("OverallUILayoutWidgetClass is not set in %s"), *GetName());
	checkf(AttributeWidgetControllerClass, TEXT("AttributeWidgetControllerClass is not set in %s"), *GetName());

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UAttributeWidgetController* WidgetController = GetAttributeWidgetController(WidgetControllerParams);
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverallUILayoutWidgetClass);
	if (IsValid(Widget))
	{
		Widget->AddToViewport();
		if (UCommonPrimaryGameLayout* PrimaryGameLayout = Cast<UCommonPrimaryGameLayout>(Widget))
		{
			OverallUILayoutWidget = PrimaryGameLayout;
			PrimaryGameLayout->SetWidgetController(WidgetController);
		}
	}

	//TODO
	if (IsValid(OverallUILayoutWidget))
	{
		for (auto& Pair : LayerClasses)
		{
			UCommonActivatableWidget* NewWidget = OverallUILayoutWidget->PushWidgetToLayerStack(Pair.Key, Pair.Value);
			if (UCommonExtendedActivatableWidget* ExtendedWidget = Cast<UCommonExtendedActivatableWidget>(NewWidget))
			{
				ExtendedWidget->SetWidgetController(WidgetController);
			}
		}
	}
}

void ACommonHUD::BeginPlay()
{
	Super::BeginPlay();
}

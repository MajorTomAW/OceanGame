// Copyright © 2023 MajorT. All rights reserved.


#include "HUD/CommonHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/CommonExtendedActivatableWidget.h"
#include "Widgets/CommonPrimaryGameLayout.h"



void ACommonHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ACommonHUD::InitOverlay()
{
	checkf(OverallUILayoutWidgetClass, TEXT("OverallUILayoutWidgetClass is not set in %s"), *GetName());

	UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerOwner, OverallUILayoutWidgetClass);
	Widget->SetOwningPlayer(PlayerOwner);
	if (IsValid(Widget))
	{
		Widget->AddToViewport();
		if (UCommonPrimaryGameLayout* PrimaryGameLayout = Cast<UCommonPrimaryGameLayout>(Widget))
		{
			OverallUILayoutWidget = PrimaryGameLayout;
		}
	}
}

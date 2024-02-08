// Copyright © 2023 MajorT. All rights reserved.


#include "Widgets/CommonPrimaryGameLayout.h"

#include "CommonActivatableWidget.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UCommonPrimaryGameLayout::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	if (IsValid(InWidgetController))
		WidgetControllerSet(InWidgetController);
}

void UCommonPrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		LayerWidget->OnTransitioningChanged.AddUObject(this, &UCommonPrimaryGameLayout::OnWidgetStackTransitioning);
		LayerWidget->SetTransitionDuration(0.f);
		Layers.Add(LayerTag, LayerWidget);
	}
}

void UCommonPrimaryGameLayout::OnWidgetStackTransitioning(UCommonActivatableWidgetContainerBase* Widget,
	bool bIsTransitioning)
{
	//TODO
	if (bIsTransitioning)
	{
		
	}
	else
	{
		
	}
}

UCommonActivatableWidgetContainerBase* UCommonPrimaryGameLayout::GetLayerWidget(FGameplayTag LayerTag)
{
	return Layers.FindRef(LayerTag);
}

void UCommonPrimaryGameLayout::FindAndRemoveWidgetFromLayer(UCommonActivatableWidget* ActivatableWidget)
{
	for (const auto& LayerKVP : Layers)
	{
		LayerKVP.Value->RemoveWidget(*ActivatableWidget);
	}
}

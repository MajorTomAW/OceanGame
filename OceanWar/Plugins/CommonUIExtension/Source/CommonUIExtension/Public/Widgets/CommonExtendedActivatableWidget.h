// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonExtendedActivatableWidget.generated.h"


/**
 * Extended version of UCommonActivatableWidget that allows for a widget controller to be set
 */
UCLASS()
class COMMONUIEXTENSION_API UCommonExtendedActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet(UObject* InWidgetController);
};

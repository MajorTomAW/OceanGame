// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonInputModeTypes.h"
#include "CommonExtendedActivatableWidget.generated.h"

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	Menu	UMETA(Tooltip = "Input is received by the UI only"),
	Game	UMETA(Tooltip = "Input is received by the Game only"),
	All		UMETA(Tooltip = "Input is received by UI and the Game"),
};


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
	virtual void OnWidgetControllerSet(UObject* InWidgetController);
	
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "On Widget Controller Set")
	void WidgetControllerSet_BP(UObject* NewWidgetController);
	
	virtual void NativeOnActivated() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	EInputMode InputMode = EInputMode::All;
};

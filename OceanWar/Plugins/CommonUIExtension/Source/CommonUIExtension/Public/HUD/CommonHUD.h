// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/HUD.h"
#include "CommonHUD.generated.h"

class UCommonExtendedActivatableWidget;
class UCommonPrimaryGameLayout;
class UAttributeWidgetController;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class COMMONUIEXTENSION_API ACommonHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UCommonPrimaryGameLayout> OverallUILayoutWidget;

	virtual void InitOverlay();
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Layouts", meta = (AllowPrivateAccess = "true"))
	TMap<UPARAM(DisplayName = "Layer Tag", meta = (Categories = "UI.Layer")) FGameplayTag, TSubclassOf<UCommonExtendedActivatableWidget>> LayerClasses;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Layouts", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCommonPrimaryGameLayout> OverallUILayoutWidgetClass;
};

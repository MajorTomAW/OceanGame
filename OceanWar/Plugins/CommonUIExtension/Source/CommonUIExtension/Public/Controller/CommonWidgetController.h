// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CommonWidgetController.generated.h"


/**
 * 
 */
UCLASS()
class COMMONUIEXTENSION_API UCommonWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CommonUIExtension|WidgetController")
	virtual void BroadcastInitialValues();
	
	virtual void BindCallbacksToDependencies();
};

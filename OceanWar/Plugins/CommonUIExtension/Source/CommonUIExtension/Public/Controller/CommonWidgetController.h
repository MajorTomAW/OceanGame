// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CommonWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY();

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, class UAbilitySystemComponent* ASC, class UAttributeSet* AS)
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonUIExtension|References")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonUIExtension|References")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonUIExtension|References")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonUIExtension|References")
	TObjectPtr<class UAttributeSet> AttributeSet;
};

/**
 * 
 */
UCLASS()
class COMMONUIEXTENSION_API UCommonWidgetController : public UObject
{
	GENERATED_BODY()

public:
	void SetWidgetControllerParams(const FWidgetControllerParams& InParams);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "CommonUIExtension|References")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "CommonUIExtension|References")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "CommonUIExtension|References")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "CommonUIExtension|References")
	TObjectPtr<class UAttributeSet> AttributeSet;
};

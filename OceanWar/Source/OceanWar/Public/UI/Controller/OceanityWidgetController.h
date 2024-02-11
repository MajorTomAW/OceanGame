// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Controller/CommonWidgetController.h"
#include "OceanityWidgetController.generated.h"

struct FGameplayTag;

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
 * Base class for all widget controllers
 */
UCLASS(BlueprintType, Blueprintable)
class OCEANWAR_API UOceanityWidgetController : public UCommonWidgetController
{
	GENERATED_BODY()
public:
	void SetWidgetControllerParams(const FWidgetControllerParams& InParams);

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
		
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

// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeDelegateWidget.h"
#include "OverallProgressBar.generated.h"

class USizeBox;
class UImage;
/**
 * 
 */
UCLASS()
class OCEANWAR_API UOverallProgressBar : public UAttributeDelegateWidget
{
	GENERATED_BODY()

public:
	UOverallProgressBar();
	
	UPROPERTY(EditAnywhere, DisplayName = "Use Editor Preview Values", Category = "Editor")
	bool bUseEditorValues = false;
	
	UPROPERTY(EditAnywhere, Category = "Editor", meta = (EditCondition = bUseEditorValues, DisplayName = "Max Value"))
	float EditorMaxValue = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Editor", meta = (EditCondition = bUseEditorValues, DisplayName = "Current Value"))
	float EditorCurrentValue = 65.0f;

	UPROPERTY(EditAnywhere, Category = "Style|Material")
	FName MaterialProgressParamName = FName("Percentage");

	UPROPERTY(EditAnywhere, Category = "Style|Tiling")
	bool bHasTiling = true;
	
	UPROPERTY(EditAnywhere, Category = "Style|Tiling", meta = (EditCondition = bHasTiling))
	FName MaterialTileParamName = FName("Tiling");
	
	UPROPERTY(EditAnywhere, Category = "Style|Tiling", meta = (EditCondition = bHasTiling));
	float SizePerTile = 30.f;

	UPROPERTY(EditAnywhere, Category = "Style|Ghost Progress")
	bool bUseGhostProgress = true;

	UPROPERTY(EditAnywhere, Category = "Style|Ghost Progress", meta = (EditCondition = bUseGhostProgress))
	FName MaterialGhostProgressParamName = FName("Ghost Percentage");
	
	UPROPERTY(EditAnywhere, Category = "Style|Ghost Progress" , meta = (EditCondition = bUseGhostProgress))
	float GhostProgressInterpSpeed = 4.0f;

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMaxValue() const { return MaxValue; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetCurrentValue() const { return CurrentValue; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetProgressPercent() const { return Percentage; }

	UFUNCTION(BlueprintCallable)
	void SetProgressPercent(float InCurrentValue, float InMaxValue);

protected:
	virtual void PrimaryAttributeValueChanged(float NewValue) override;
	virtual void SecondaryAttributeValueChanged(float NewValue) override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativePreConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ProgressBarImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> ProgressBarSizeBox;
	
private:
	float MaxValue = 0.f;
	float CurrentValue = 0.f;
	float Percentage = 0.f;
	float GhostPercentage = 0.f;
	float TargetGhostPercentage = 0.f;
};

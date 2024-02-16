// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Widgets/OverallProgressBar.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Kismet/KismetMathLibrary.h"

UOverallProgressBar::UOverallProgressBar()
{
	if (ProgressBarImage)
	{
		if (bHasTiling)
			ProgressBarSizeBox->SetWidthOverride(MaxValue * SizePerTile * 0.1f);
	}
}

void UOverallProgressBar::SetProgressPercent(float InCurrentValue, float InMaxValue)
{
	Percentage = UKismetMathLibrary::SafeDivide(InCurrentValue, InMaxValue);
	if (UMaterialInstanceDynamic* ProgressMat = ProgressBarImage->GetDynamicMaterial())
	{
		ProgressMat->SetScalarParameterValue(MaterialProgressParamName, Percentage);
	}
	if (bUseGhostProgress)
		TargetGhostPercentage = Percentage;
}

void UOverallProgressBar::PrimaryAttributeValueChanged(float NewValue)
{
	CurrentValue = NewValue;
	SetProgressPercent(CurrentValue, MaxValue);
	PrimaryAttributeValueChanged_BP(NewValue);
	OnPrimaryAttributeValueChanged.Broadcast(NewValue);
}

void UOverallProgressBar::SecondaryAttributeValueChanged(float NewValue)
{
	MaxValue = NewValue;
	SetProgressPercent(CurrentValue, MaxValue);

	if (ProgressBarSizeBox)
	{
		if (bHasTiling)
			ProgressBarSizeBox->SetWidthOverride(MaxValue * SizePerTile * 0.1f);
		
		if (UMaterialInstanceDynamic* ProgressMat = ProgressBarImage->GetDynamicMaterial())
		{
			if (bHasTiling)
			{
				ProgressMat->SetScalarParameterValue(MaterialTileParamName, MaxValue * 0.1f);	
			}
			else
			{
				ProgressMat->SetScalarParameterValue(MaterialTileParamName, 1.f);
			}
		}
	}

	SecondaryAttributeValueChanged_BP(NewValue);
	OnSecondaryAttributeValueChanged.Broadcast(NewValue);
}

void UOverallProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bUseGhostProgress)
	{
		GhostPercentage = 0.f;
		TargetGhostPercentage = 0.f;
		return;
	}
	GhostPercentage = FMath::FInterpTo(GhostPercentage, TargetGhostPercentage, InDeltaTime, GhostProgressInterpSpeed);
	if (UMaterialInstanceDynamic* ProgressMat = ProgressBarImage->GetDynamicMaterial())
	{
		ProgressMat->SetScalarParameterValue(MaterialGhostProgressParamName, GhostPercentage);
	}
}

void UOverallProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();
	const bool bPreview = IsDesignTime() && bUseEditorValues;
	if (!bPreview) return;

	if (bHasTiling)
		ProgressBarSizeBox->SetWidthOverride(EditorMaxValue * SizePerTile * 0.1f);
	SetProgressPercent(EditorCurrentValue, EditorMaxValue);
	
	if (UMaterialInstanceDynamic* ProgressMat = ProgressBarImage->GetDynamicMaterial())
	{
		if (bHasTiling)
		{
			ProgressMat->SetScalarParameterValue(MaterialTileParamName, EditorMaxValue * 0.1f);	
		}
		else
		{
			ProgressMat->SetScalarParameterValue(MaterialTileParamName, 1.f);
		}
	}
}

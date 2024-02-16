// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OceanityAbilityFunctionLibrary.generated.h"


class UAbilitySystemComponent;
struct FGameplayTag;

USTRUCT(BlueprintType)
struct FRangedMontageSection
{
	GENERATED_BODY()

	FRangedMontageSection() {};
	FRangedMontageSection(FName InSectionName, float InMinValue, float InMaxValue)
		: SectionName(InSectionName), MinValue(InMinValue), MaxValue(InMaxValue) {};
	
	FName SectionName = FName();
	float MinValue = 0.f;
	float MaxValue = 0.f;
};

/**
 * 
 */
UCLASS()
class OCEANWAR_API UOceanityAbilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Widget Controller */
	UFUNCTION(BlueprintPure, Category = "CommonUI|Controller", meta = (WorldContext = "WorldContextObject", Keywords = "Attribute Widget Controller"))
	static UPARAM(DisplayName = "Widget Controller") class UAttributeWidgetController* GetAttributeWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "CommonUI|Controller", meta = (WorldContext = "WorldContextObject", Keywords = "Ship Customization Widget Controller"))
	static UPARAM(DisplayName = "Widget Controller") class UShipCustomizationWidgetController* GetShipCustomizationWidgetController(const UObject* WorldContextObject);

	/** Initializing */
	UFUNCTION(BlueprintCallable, Category = "CommonAbilitySystem|Defaults", meta = (DisplayName = "Initialize Default Attributes", WorldContext = "WorldContextObject"))
	static void InitializeDefaultAttribute(const UObject* WorldContextObject, ETurretClassType TurretClass, EEngineClassType EngineClass, EHullClassType HullClass, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "CommonAbilitySystem|Defaults", meta = (DisplayName = "Add Startup Abilities", WorldContext = "WorldContextObject"))
	static void AddStartupAbilities(const UObject* WorldContextObject, ETurretClassType TurretClass, EEngineClassType EngineClass, EHullClassType HullClass, UAbilitySystemComponent* ASC);

	/** Animations */
	UFUNCTION(BlueprintCallable, Category = "CommonAbilitySystem|Animations", meta = (DisplayName = "Get Montage Section based on Ranged Float"))
	static FName GetMontageSectionBasedOnRangedFloat(float Value, TArray<FRangedMontageSection> Sections);

	UFUNCTION(BlueprintPure, Category = "CommonAbilitySystem|Animations", meta = (DisplayName = "Make Ranged Section from Vector2D"))
	static FRangedMontageSection MakeRangedMontageSectionVector2D(FName SectionName, FVector2D Range)
	{
		return FRangedMontageSection(SectionName, Range.X, Range.Y);
	};
};

// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/Data/Attributes/AbilityInputInfo.h"
#include "OceanityAbilityFunctionLibrary.generated.h"


enum class ETurretClassType : uint8;
enum class EEngineClassType : uint8;
enum class EHullClassType : uint8;
struct FGameplayAbilitySpec;
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

	UFUNCTION(BlueprintCallable, Category = "CommonAbilitySystem|Rewards", meta = (DisplayName = "Get Earned Coins", WorldContext = "WorldContextObject"))
	static int32 GetEarnedCoins(const UObject* WorldContextObject, const FGameplayTagContainer& DamageTags);

	/** Animations */
	UFUNCTION(BlueprintCallable, Category = "CommonAbilitySystem|Animations", meta = (DisplayName = "Get Montage Section based on Ranged Float"))
	static FName GetMontageSectionBasedOnRangedFloat(float Value, TArray<FRangedMontageSection> Sections);

	UFUNCTION(BlueprintPure, Category = "CommonAbilitySystem|Animations", meta = (DisplayName = "Make Ranged Section from Vector2D"))
	static FRangedMontageSection MakeRangedMontageSectionVector2D(FName SectionName, FVector2D Range)
	{
		return FRangedMontageSection(SectionName, Range.X, Range.Y);
	};


	// Ability
	UFUNCTION(BlueprintPure, Category = "CommonAbilitySystem|Ability", meta = (DisplayName = "Get Ability Tag"))
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& Spec, FGameplayTag TagToLookFor = FGameplayTag());

	UFUNCTION(BlueprintPure, Category = "CommonAbilitySystem|Ability", meta = (DisplayName = "Get Ability Input Tag"))
	static FGameplayTag GetAbilityInputTagFromSpec(const FGameplayAbilitySpec& Spec, FGameplayTag TagToLookFor = FGameplayTag());

	UFUNCTION(BlueprintPure, Category = "CommonAbilitySystem|Ability", meta = (DisplayName = "Get Ability Input Info"))
	static FOceanityAbilityInputInfo GetAbilityInputInfoFromTag(const FGameplayTag& Spec, const UAbilityInputInfo* InputDataAsset);
};

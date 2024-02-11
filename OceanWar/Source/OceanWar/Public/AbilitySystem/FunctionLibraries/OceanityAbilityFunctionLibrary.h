// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OceanityAbilityFunctionLibrary.generated.h"


class UAbilitySystemComponent;
struct FGameplayTag;

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
};

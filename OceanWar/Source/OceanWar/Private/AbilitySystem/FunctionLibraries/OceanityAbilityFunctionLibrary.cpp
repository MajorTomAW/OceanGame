// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/FunctionLibraries/OceanityAbilityFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/OceanityAbilityComponent.h"
#include "AbilitySystem/Data/Ship/EngineClassInfo.h"
#include "AbilitySystem/Data/Ship/HullClassInfo.h"
#include "AbilitySystem/Data/Ship/ShipClassInfo.h"
#include "AbilitySystem/Data/Ship/TurretClassInfo.h"
#include "GameMode/OceanityGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerState/OceanityPlayerState.h"
#include "UI/Controller/OceanityWidgetController.h"
#include "UI/HUD/OceanityHUD.h"

UAttributeWidgetController* UOceanityAbilityFunctionLibrary::GetAttributeWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AOceanityHUD* OceanityHUD = Cast<AOceanityHUD>(PC->GetHUD()))
		{
			AOceanityPlayerState* PS = PC->GetPlayerState<AOceanityPlayerState>();
			const FWidgetControllerParams Params{PC, PS, PS->GetAbilitySystemComponent(), PS->GetAttributeSet()};
			return OceanityHUD->GetAttributeWidgetController(Params);
		}
	}
	return nullptr;
}

UShipCustomizationWidgetController* UOceanityAbilityFunctionLibrary::GetShipCustomizationWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AOceanityHUD* OceanityHUD = Cast<AOceanityHUD>(PC->GetHUD()))
		{
			AOceanityPlayerState* PS = PC->GetPlayerState<AOceanityPlayerState>();
			const FWidgetControllerParams Params{PC, PS, PS->GetAbilitySystemComponent(), PS->GetAttributeSet()};
			return OceanityHUD->GetShipCustomizationWidgetController(Params);
		}
	}
	return nullptr;
}

void UOceanityAbilityFunctionLibrary::InitializeDefaultAttribute(
	const UObject* WorldContextObject,
	ETurretClassType TurretClass,
	EEngineClassType EngineClass,
	EHullClassType HullClass,
	UAbilitySystemComponent* ASC)
{
	if (const AOceanityGameMode* GMB = Cast<AOceanityGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		const FShipClassDefaultInfo TurretDefaults = GMB->TurretClassDefaults->GetTurretClassDefaults(TurretClass);
		const FShipClassDefaultInfo EngineDefaults = GMB->EngineClassDefaults->GetEngineClassDefaults(EngineClass);
		const FShipClassDefaultInfo HullDefaults = GMB->HullClassDefaults->GetHullClassDefaults(HullClass);
		const TSubclassOf<UGameplayEffect> InitialGameplayEffect = GMB->InitialGameplayEffect;
		const TSubclassOf<UGameplayEffect> DerivedInitialGameplayEffect = GMB->DerivedInitialGameplayEffect;

		if (!ASC) return;

		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		Context.AddSourceObject(WorldContextObject);

		/** Attributes */
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(InitialGameplayEffect, 1.f, Context);
		TMap<FGameplayTag, float> InitialDefaults;
		InitialDefaults.Append(TurretDefaults.DefaultAttributes);
		InitialDefaults.Append(EngineDefaults.DefaultAttributes);
		InitialDefaults.Append(HullDefaults.DefaultAttributes);

		for (const auto& Pair : InitialDefaults)
		{
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, Pair.Value);
		}
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

		/** Derived Attributes */
		const FGameplayEffectSpecHandle DerivedSpecHandle = ASC->MakeOutgoingSpec(DerivedInitialGameplayEffect, 1.f, Context);
		TMap<FGameplayTag, float> DerivedInitialDefaults;
		DerivedInitialDefaults.Append(TurretDefaults.DefaultDerivedAttributes);
		DerivedInitialDefaults.Append(EngineDefaults.DefaultDerivedAttributes);
		DerivedInitialDefaults.Append(HullDefaults.DefaultDerivedAttributes);

		for (const auto& Pair : DerivedInitialDefaults)
		{
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DerivedSpecHandle, Pair.Key, Pair.Value);
		}
		ASC->ApplyGameplayEffectSpecToSelf(*DerivedSpecHandle.Data.Get());
	}
}

void UOceanityAbilityFunctionLibrary::AddStartupAbilities(
	const UObject* WorldContextObject,
	ETurretClassType TurretClass,
	EEngineClassType EngineClass,
	EHullClassType HullClass,
	UAbilitySystemComponent* ASC)
{
	if (!ASC) return;

	if (const AOceanityGameMode* GMB = Cast<AOceanityGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		const FShipClassDefaultInfo TurretDefaults = GMB->TurretClassDefaults->GetTurretClassDefaults(TurretClass);
		const FShipClassDefaultInfo EngineDefaults = GMB->EngineClassDefaults->GetEngineClassDefaults(EngineClass);
		const FShipClassDefaultInfo HullDefaults = GMB->HullClassDefaults->GetHullClassDefaults(HullClass);
		TArray<TSubclassOf<UGameplayAbility>> InitialAbilities;

		// Abilities
		InitialAbilities.Append(TurretDefaults.DefaultAbilities);
		InitialAbilities.Append(EngineDefaults.DefaultAbilities);
		InitialAbilities.Append(HullDefaults.DefaultAbilities);

		// Common Abilities
		InitialAbilities.Append(GMB->TurretClassDefaults->CommonAbilities);
		InitialAbilities.Append(GMB->EngineClassDefaults->CommonAbilities);
		InitialAbilities.Append(GMB->HullClassDefaults->CommonAbilities);

		if (UOceanityAbilityComponent* OceanityASC = CastChecked<UOceanityAbilityComponent>(ASC))
		{
			OceanityASC->AddStartupGameplayAbilities(InitialAbilities);
		}
	}
}

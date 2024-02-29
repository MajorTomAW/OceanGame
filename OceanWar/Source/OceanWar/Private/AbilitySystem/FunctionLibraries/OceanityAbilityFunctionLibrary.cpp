// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/FunctionLibraries/OceanityAbilityFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "OceanityGameTags.h"
#include "AbilitySystem/OceanityAbilityComponent.h"
#include "AbilitySystem/Data/Cashout/CoinEarnInfo.h"
#include "AbilitySystem/Data/Ship/EngineClassInfo.h"
#include "AbilitySystem/Data/Ship/HullClassInfo.h"
#include "AbilitySystem/Data/Ship/ShipClassInfo.h"
#include "AbilitySystem/Data/Ship/TurretClassInfo.h"
#include "AbilitySystem/Data/Ship/AbilitySet/ShipAbilitySetInfo.h"
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
		InitialDefaults.Append(TurretDefaults.AbilitySetAsset->DefaultAttributes);
		InitialDefaults.Append(EngineDefaults.AbilitySetAsset->DefaultAttributes);
		InitialDefaults.Append(HullDefaults.AbilitySetAsset->DefaultAttributes);

		for (const auto& Pair : InitialDefaults)
		{
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, Pair.Value);
		}
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

		/** Derived Attributes */
		const FGameplayEffectSpecHandle DerivedSpecHandle = ASC->MakeOutgoingSpec(DerivedInitialGameplayEffect, 1.f, Context);
		TMap<FGameplayTag, float> DerivedInitialDefaults;
		DerivedInitialDefaults.Append(TurretDefaults.AbilitySetAsset->DefaultDerivedAttributes);
		DerivedInitialDefaults.Append(EngineDefaults.AbilitySetAsset->DefaultDerivedAttributes);
		DerivedInitialDefaults.Append(HullDefaults.AbilitySetAsset->DefaultDerivedAttributes);

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
		InitialAbilities.Append(TurretDefaults.AbilitySetAsset->DefaultAbilities);
		InitialAbilities.Append(EngineDefaults.AbilitySetAsset->DefaultAbilities);
		InitialAbilities.Append(HullDefaults.AbilitySetAsset->DefaultAbilities);

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

int32 UOceanityAbilityFunctionLibrary::GetEarnedCoins(
	const UObject* WorldContextObject,
	const FGameplayTagContainer& DamageTags)
{
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(WorldContextObject);
	if (const AOceanityGameMode* GMB = Cast<AOceanityGameMode>(GameModeBase))
	{
		return GMB->CoinEarnInfoDefaults->GetCoinsEarned(DamageTags);
	}
	return 0;
}

FName UOceanityAbilityFunctionLibrary::GetMontageSectionBasedOnRangedFloat(float Value,
                                                                           TArray<FRangedMontageSection> Sections)
{
	for (const auto& Section : Sections)
	{
		if (Section.MinValue <= Value && Section.MaxValue >= Value)
		{
			return Section.SectionName;
		}
	}
	return FName("None");
}

FGameplayTag UOceanityAbilityFunctionLibrary::GetAbilityTagFromSpec(const FGameplayAbilitySpec& Spec,
	FGameplayTag TagToLookFor)
{
	if (!TagToLookFor.IsValid())
	{
		TagToLookFor = OceanityGameplayTags::Ability::Tag_Ability;
	}

	if (Spec.Ability)
	{
		for (const FGameplayTag& Tag : Spec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(TagToLookFor))
			{
				return Tag;
			}
		}
	}

	return FGameplayTag::EmptyTag;
}

FGameplayTag UOceanityAbilityFunctionLibrary::GetAbilityInputTagFromSpec(const FGameplayAbilitySpec& Spec,
	FGameplayTag TagToLookFor)
{
	if (!TagToLookFor.IsValid())
	{
		TagToLookFor = OceanityGameplayTags::Input::Tag_InputTag;
	}

	if (Spec.Ability)
	{
		for (const FGameplayTag& DynamicTag : Spec.DynamicAbilityTags)
		{
			if (DynamicTag.MatchesTag(TagToLookFor))
			{
				return DynamicTag;
			}
		}
	}

	return FGameplayTag::EmptyTag;
}

FOceanityAbilityInputInfo UOceanityAbilityFunctionLibrary::GetAbilityInputInfoFromTag(const FGameplayTag& Spec,
                                                                                      const UAbilityInputInfo* InputDataAsset)
{
	if (InputDataAsset)
	{
		return InputDataAsset->FindAbilityInputInfoByTag(Spec);
	}
	return FOceanityAbilityInputInfo();
}



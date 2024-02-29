// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Controller/AttributeWidgetController.h"

#include "CommonAttributeSet.h"
#include "AbilitySystem/OceanityAbilityComponent.h"
#include "AbilitySystem/FunctionLibraries/OceanityAbilityFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerState/OceanityPlayerState.h"
#include "UI/Data/Attributes/AbilityInfo.h"

void UAttributeWidgetController::BroadcastInitialValues()
{
	UCommonAttributeSet* AS = Cast<UCommonAttributeSet>(this->AttributeSet);
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());		
	}

	if (UOceanityAbilityComponent* OceanityASC = Cast<UOceanityAbilityComponent>(AbilitySystemComponent))
	{
		if (OceanityASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(OceanityASC);
		}
		else
		{
			OceanityASC->OnAbilitiesGivenDelegate.AddUObject(this, &ThisClass::OnInitializeStartupAbilities);	
		}
	}
}

void UAttributeWidgetController::BindCallbacksToDependencies()
{
	AOceanityPlayerState* PS = CastChecked<AOceanityPlayerState>(PlayerState);
	UCommonAttributeSet* AS = Cast<UCommonAttributeSet>(this->AttributeSet);

	PS->OnCoinsChanged.AddUObject(this, &ThisClass::OnPlayerCoinsChanged);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			});
	}

	
}

void UAttributeWidgetController::OnInitializeStartupAbilities(UOceanityAbilityComponent* AbilityComponent) const
{
	if (!AbilityComponent->bStartupAbilitiesGiven) return;

	FForEachAbilitySignature Delegate;
	Delegate.BindLambda(
		[this] (const FGameplayAbilitySpec& Spec)
		{
			FOceanityAbilityInfo AbilityInfo = AbilityDataAsset->FindAbilityInfoByTag(UOceanityAbilityFunctionLibrary::GetAbilityTagFromSpec(Spec));
			if (!AbilityInfo.AbilityTag.IsValid() || !AbilityInfo.bShouldShowInUI) return;
			AbilityInfo.InputTag = UOceanityAbilityFunctionLibrary::GetAbilityInputTagFromSpec(Spec);
			AbilityInfo.InputInfo = UOceanityAbilityFunctionLibrary::GetAbilityInputInfoFromTag(AbilityInfo.InputTag, AbilityInputDataAsset);
			UKismetSystemLibrary::PrintString(this, Spec.Ability->GetName(), true, false, FLinearColor::Green, 5.f);
			OnAbilityInfoChangedDelegate.Broadcast(AbilityInfo);
		});

	AbilityComponent->ForEachAbility(Delegate);
}

void UAttributeWidgetController::OnPlayerCoinsChanged(int32 NewCoins, int32 OldCoins)
{
	const int32 DeltaCoins = NewCoins - OldCoins;
	OnPlayerCoinsChangedDelegate.Broadcast(NewCoins, DeltaCoins);
}

void UAttributeWidgetController::BroadcastAttributeInfo(const FGameplayTag& Tag, const FGameplayAttribute& Attribute) const
{
	OnAttributeValueChangedDelegate.Broadcast(Tag, Attribute.GetNumericValue(AttributeSet));
}

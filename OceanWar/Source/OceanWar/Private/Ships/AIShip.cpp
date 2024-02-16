// Copyright © 2024 MajorT. All rights reserved.


#include "Ships/AIShip.h"

#include "AbilitySystem/OceanityAbilityComponent.h"
#include "AbilitySystem/OceanityAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CommonExtendedActivatableWidget.h"


AAIShip::AAIShip()
{
	AbilitySystemComponent = CreateDefaultSubobject<UOceanityAbilityComponent>(TEXT("AbilitySystemComponent"));
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetIsReplicated(true);
		AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Minimal;	
	}
	
	AttributeSet = CreateDefaultSubobject<UOceanityAttributeSet>(TEXT("AttributeSet"));

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	if (HealthBarWidgetComponent)
	{
		HealthBarWidgetComponent->SetupAttachment(GetMesh());
		HealthBarWidgetComponent->SetDrawAtDesiredSize(true);
		HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	}
}

void AAIShip::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	BindToAttributeDelegates();
	if (UCommonExtendedActivatableWidget* Widget = Cast<UCommonExtendedActivatableWidget>(HealthBarWidgetComponent->GetUserWidgetObject()))
	{
		Widget->SetWidgetController(this);
		BroadcastInitialAttributes();
	}
}

void AAIShip::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
	AddStartupGameplayAbilities();
}

void AAIShip::BroadcastInitialAttributes()
{
	if (UOceanityAttributeSet* AS = Cast<UOceanityAttributeSet>(AttributeSet))
	{
		for (auto& Pair : AS->TagsToAttributes)
		{
			OnAttributeValueChangedDelegate.Broadcast(Pair.Key, Pair.Value().GetNumericValue(AttributeSet));
		}
	}
}

void AAIShip::BindToAttributeDelegates()
{
	if (UOceanityAttributeSet* AS = Cast<UOceanityAttributeSet>(AttributeSet))
	{
		for (auto& Pair : AS->TagsToAttributes)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
				[this, Pair](const FOnAttributeChangeData& Data)
				{
					OnAttributeValueChangedDelegate.Broadcast(Pair.Key, Pair.Value().GetNumericValue(AttributeSet));
				});
		}
	}
}


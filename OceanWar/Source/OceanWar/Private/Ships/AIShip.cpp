// Copyright © 2024 MajorT. All rights reserved.


#include "Ships/AIShip.h"

#include "AbilitySystem/OceanityAbilityComponent.h"
#include "AbilitySystem/OceanityAttributeSet.h"
#include "Components/WidgetComponent.h"


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
}

void AAIShip::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
	AddStartupGameplayAbilities();
}


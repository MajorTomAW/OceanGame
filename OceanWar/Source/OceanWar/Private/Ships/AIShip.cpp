// Copyright © 2024 MajorT. All rights reserved.


#include "Ships/AIShip.h"

#include "CommonAbilityComponent.h"
#include "CommonAttributeSet.h"


AAIShip::AAIShip()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCommonAbilityComponent>(TEXT("AbilitySystemComponent"));
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetIsReplicated(true);
		AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Minimal;	
	}
	
	AttributeSet = CreateDefaultSubobject<UCommonAttributeSet>(TEXT("AttributeSet"));
}

void AAIShip::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AAIShip::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}


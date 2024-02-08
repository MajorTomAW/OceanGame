// Copyright © 2024 MajorT. All rights reserved.


#include "PlayerState/OceanityPlayerState.h"

#include "CommonAbilityComponent.h"
#include "CommonAttributeSet.h"

AOceanityPlayerState::AOceanityPlayerState()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UCommonAbilityComponent>(TEXT("AbilitySystemComponent"));
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetIsReplicated(true);
		AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	}
	
	AttributeSet = CreateDefaultSubobject<UCommonAttributeSet>(TEXT("AttributeSet"));
}

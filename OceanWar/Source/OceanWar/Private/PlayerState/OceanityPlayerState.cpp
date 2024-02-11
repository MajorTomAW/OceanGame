// Copyright © 2024 MajorT. All rights reserved.


#include "PlayerState/OceanityPlayerState.h"

#include "AbilitySystem/OceanityAbilityComponent.h"
#include "AbilitySystem/OceanityAttributeSet.h"

AOceanityPlayerState::AOceanityPlayerState()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UOceanityAbilityComponent>(TEXT("AbilitySystemComponent"));
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetIsReplicated(true);
		AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	}
	
	AttributeSet = CreateDefaultSubobject<UOceanityAttributeSet>(TEXT("AttributeSet"));
}

// Copyright © 2024 MajorT. All rights reserved.


#include "PlayerState/OceanityPlayerState.h"

#include "AbilitySystem/OceanityAbilityComponent.h"
#include "AbilitySystem/OceanityAttributeSet.h"
#include "Net/UnrealNetwork.h"

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

void AOceanityPlayerState::AddCoins(int32 InCoins)
{
	const int32 OldCoins = Coins;
	Coins += InCoins;
	OnCoinsChanged.Broadcast(Coins, OldCoins);
}

void AOceanityPlayerState::SetCoins(int32 InCoins)
{
	const int32 OldCoins = Coins;
	Coins = InCoins;
	OnCoinsChanged.Broadcast(Coins, OldCoins);
}

void AOceanityPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AOceanityPlayerState, Coins);
}

void AOceanityPlayerState::OnRep_Coins(int32 OldCoins)
{
	OnCoinsChanged.Broadcast(Coins, OldCoins);
}

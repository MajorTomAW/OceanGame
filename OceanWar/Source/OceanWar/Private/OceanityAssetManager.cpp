// Copyright © 2024 MajorT. All rights reserved.


#include "OceanityAssetManager.h"
#include "AbilitySystemGlobals.h"

UOceanityAssetManager& UOceanityAssetManager::Get()
{
	check(GEngine);
	UOceanityAssetManager* This = Cast<UOceanityAssetManager>(GEngine->AssetManager);
	return *This;
}

void UOceanityAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// Required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}

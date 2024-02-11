// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "OceanityAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UOceanityAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UOceanityAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};

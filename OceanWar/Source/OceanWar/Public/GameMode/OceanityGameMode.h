// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OceanityGameMode.generated.h"

class UGameplayEffect;
class UEngineClassInfo;
class UTurretClassInfo;
class UHullClassInfo;
/**
 * 
 */
UCLASS()
class OCEANWAR_API AOceanityGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShipClassDefaults")
	TObjectPtr<UTurretClassInfo> TurretClassDefaults;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShipClassDefaults")
	TObjectPtr<UEngineClassInfo> EngineClassDefaults;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShipClassDefaults")
	TObjectPtr<UHullClassInfo> HullClassDefaults;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShipClassDefaults")
	TSubclassOf<UGameplayEffect> InitialGameplayEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShipClassDefaults")
	TSubclassOf<UGameplayEffect> DerivedInitialGameplayEffect;
};

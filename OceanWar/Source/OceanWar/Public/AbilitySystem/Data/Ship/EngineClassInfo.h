// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShipClassInfo.h"
#include "EngineClassInfo.generated.h"

UENUM(BlueprintType)
enum class EEngineClassType : uint8
{
	None,
	OceanityEngine,
	OceanityEnginePlus,
	BoosterEngine,
	TankEngine,
};

/**
 * Engine class type
 * Specifies the type of engine class, which is used to determine the default attributes and abilities of the engine
 */
UCLASS()
class OCEANWAR_API UEngineClassInfo : public UShipClassInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TMap<EEngineClassType, FShipClassDefaultInfo> EngineClassDefaults;

	FShipClassDefaultInfo GetEngineClassDefaults(EEngineClassType EngineClassType);
};

// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShipClassInfo.h"
#include "TurretClassInfo.generated.h"

UENUM(BlueprintType)
enum class ETurretClassType : uint8
{
	None,
	OceanityTurret,
	Triplet,
	Sniper,
	Sprayer,
	Shotgun,
	Missile,
	Laser,
	Arsonist,
};

/**
 * Turret class type
 * Specifies the type of turret, which is used to determine the default attributes and abilities of the turret
 */
UCLASS()
class OCEANWAR_API UTurretClassInfo : public UShipClassInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<ETurretClassType, FShipClassDefaultInfo> TurretClassDefaults;

	FShipClassDefaultInfo GetTurretClassDefaults(ETurretClassType TurretClassType);
};

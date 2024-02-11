// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShipClassInfo.h"
#include "HullClassInfo.generated.h"

UENUM(BlueprintType)
enum class EHullClassType : uint8
{
	None,
	OceanityHull,
	OceanityHullPlus,
	HeavyHull,
	LightHull,
};

/**
 * Hull class type
 * Specifies the type of hull class, which is used to determine the default attributes and abilities of the hull
 */
UCLASS()
class OCEANWAR_API UHullClassInfo : public UShipClassInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<EHullClassType, FShipClassDefaultInfo> HullClassDefaults;

	FShipClassDefaultInfo GetHullClassDefaults(EHullClassType HullClassType);
};

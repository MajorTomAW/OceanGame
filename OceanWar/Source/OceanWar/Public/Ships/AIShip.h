// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "OceanityShip.h"
#include "AIShip.generated.h"

class UWidgetComponent;

UCLASS()
class OCEANWAR_API AAIShip : public AOceanityShip
{
	GENERATED_BODY()

public:
	AAIShip();

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UWidgetComponent> HealthBarWidgetComponent;
};

// Copyright © 2024 MajorT. All rights reserved.

#include "WaterSubsystem.h"
#include "CommonWaterBodyActor.h"
#include "EngineUtils.h"

void UWaterSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (const ACommonWaterBodyActor* WaterActor : TActorRange<ACommonWaterBodyActor>(GetWorld()))
	{
		if (WaterActor)
		{
			WaterActor->Update();
		}
	}
}

TStatId UWaterSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UWaterSubsystem, STATGROUP_Tickables);
}

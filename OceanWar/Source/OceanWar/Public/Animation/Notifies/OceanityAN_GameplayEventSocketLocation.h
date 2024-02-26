// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "OceanityAN_GameplayEventSocketLocation.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UOceanityAN_GameplayEventSocketLocation : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override
	{
		return TEXT("Send Gameplay Event");
	}

	virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Event")
	FGameplayTag EventTag;
};

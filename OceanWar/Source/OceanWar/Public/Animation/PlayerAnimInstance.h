// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "OceanityAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UPlayerAnimInstance : public UOceanityAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintPure, Category = "PlayerAnimInstance", meta = (CompactNodeTitle = "Aim Pitch"))
	float GetAimPitch() const { return AimPitch; }

	UFUNCTION(BlueprintPure, Category = "PlayerAnimInstance", meta = (CompactNodeTitle = "Aim Yaw"))
	float GetAimYaw() const { return AimYaw; }

	UFUNCTION(BlueprintPure, Category = "PlayerAnimInstance", meta = (CompactNodeTitle = "Local Aim Yaw"))
	float GetLocalAimYaw() const { return AimYaw - OwnedCharacterRotation.Yaw; }
	
private:
	float AimPitch;
	float AimYaw;
};

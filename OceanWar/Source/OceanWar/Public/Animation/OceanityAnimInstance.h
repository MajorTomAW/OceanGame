// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OceanityAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UOceanityAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "OceanityAnimInstance")
	TObjectPtr<ACharacter> OwnedCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "OceanityAnimInstance", meta = (AllowPrivateAccess = "true"))
	FRotator OwnedCharacterRotation;

private:
	UPROPERTY(BlueprintReadOnly, Category = "OceanityAnimInstance", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "OceanityAnimInstance", meta = (AllowPrivateAccess = "true"))
	float SpeedZ;

	UPROPERTY(BlueprintReadOnly, Category = "OceanityAnimInstance", meta = (AllowPrivateAccess = "true"))
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "OceanityAnimInstance", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;
};

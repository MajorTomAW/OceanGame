// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "OceanityAN_PlayWeaponMontage.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UOceanityAN_PlayWeaponMontage : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	float RateScale = 1.0f;
};

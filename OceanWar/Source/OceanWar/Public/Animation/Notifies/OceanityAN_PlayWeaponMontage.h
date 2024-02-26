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

public:
	UOceanityAN_PlayWeaponMontage();

	virtual FString GetNotifyName_Implementation() const override
	{
		return TEXT("Play Weapon Montage");
	}
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	float RateScale = 1.0f;
};

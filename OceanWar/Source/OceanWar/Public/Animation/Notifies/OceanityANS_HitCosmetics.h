// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "OceanityANS_HitCosmetics.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UOceanityANS_HitCosmetics : public UAnimNotifyState
{
	GENERATED_BODY()
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Material")
	TObjectPtr<UMaterialInterface> HitMaterial;

	UPROPERTY()
	TObjectPtr<UMaterialInterface> OriginalMaterial;
};

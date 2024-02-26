// Copyright © 2024 MajorT. All rights reserved.


#include "Animation/Notifies/OceanityANS_HitCosmetics.h"

void UOceanityANS_HitCosmetics::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	checkf(HitMaterial, TEXT("HitMaterial is not set in %s"), *GetName());
	if (const AActor* Owner = MeshComp->GetOwner())
	{
		TArray<UMeshComponent*> MeshComponents;
		Owner->GetComponents<UMeshComponent>(MeshComponents, true);
		
		for (UMeshComponent* Mesh : MeshComponents)
		{
			OriginalMaterial = Mesh->GetOverlayMaterial();
			Mesh->SetOverlayMaterial(HitMaterial);
			Mesh->CustomDepthStencilValue = 1;
		}
	}

	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UOceanityANS_HitCosmetics::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (const AActor* Owner = MeshComp->GetOwner())
	{
		TArray<UMeshComponent*> MeshComponents;
		Owner->GetComponents<UMeshComponent>(MeshComponents, true);
		
		for (UMeshComponent* Mesh : MeshComponents)
		{
			Mesh->SetOverlayMaterial(OriginalMaterial);
			Mesh->CustomDepthStencilValue = 2;
		}
	}
	
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

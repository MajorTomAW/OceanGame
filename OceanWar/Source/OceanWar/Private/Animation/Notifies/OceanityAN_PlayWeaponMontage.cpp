// Copyright © 2024 MajorT. All rights reserved.


#include "Animation/Notifies/OceanityAN_PlayWeaponMontage.h"

#include "Equipment/Components/OceanityEquipmentComponent.h"
#include "Interfaces/CombatInterface.h"

UOceanityAN_PlayWeaponMontage::UOceanityAN_PlayWeaponMontage()
{
}

void UOceanityAN_PlayWeaponMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	return;
}

void UOceanityAN_PlayWeaponMontage::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotify(BranchingPointPayload);

	const UAnimMontage* MontageLeader = Cast<UAnimMontage>(BranchingPointPayload.SequenceAsset);
	const APawn* Pawn = Cast<APawn>(BranchingPointPayload.SkelMeshComponent->GetOwner());
	UAnimMontage* WeaponMontage = nullptr;
	UAnimInstance* FollowerAnimInstance = nullptr;

	if (const UOceanityEquipmentComponent* EquipmentComponent = UOceanityEquipmentComponent::FindEquipmentComponent(Pawn))
	{
		WeaponMontage = EquipmentComponent->TurretInfo.MeshInfoAsset->AttackMontage;
	}

	if (const ICombatInterface* CombatInterfacePtr = Cast<ICombatInterface>(Pawn))
	{
		FollowerAnimInstance = CombatInterfacePtr->GetWeaponMesh() ? CombatInterfacePtr->GetWeaponMesh()->GetAnimInstance() : nullptr;
	}

	if (WeaponMontage && FollowerAnimInstance)
	{
		FollowerAnimInstance->Montage_Play(WeaponMontage, RateScale, EMontagePlayReturnType::MontageLength, 0.f, true);
		FollowerAnimInstance->MontageSync_Follow(nullptr, BranchingPointPayload.SkelMeshComponent->GetAnimInstance(), MontageLeader);
	}
}

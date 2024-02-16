// Copyright © 2024 MajorT. All rights reserved.


#include "Animation/Notifies/OceanityAN_PlayWeaponMontage.h"

#include "Interfaces/CombatInterface.h"

void UOceanityAN_PlayWeaponMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	const UAnimMontage* MontageLeader = Cast<UAnimMontage>(Animation);
	const APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(Pawn))
	{
		UAnimMontage* WeaponMontage = CombatInterface->GetWeaponMontage();
		UAnimInstance* FollowerAnimInstance = CombatInterface->GetWeaponMesh()->GetAnimInstance();

		if (WeaponMontage && FollowerAnimInstance)
		{
			FollowerAnimInstance->Montage_Play(WeaponMontage, RateScale, EMontagePlayReturnType::MontageLength, 0.f, true);
			FollowerAnimInstance->MontageSync_Follow(nullptr, MeshComp->GetAnimInstance(), MontageLeader);
		}
	}
}

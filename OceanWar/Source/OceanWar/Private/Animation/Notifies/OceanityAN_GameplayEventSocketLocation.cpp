// Copyright © 2024 MajorT. All rights reserved.


#include "Animation/Notifies/OceanityAN_GameplayEventSocketLocation.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Equipment/Components/OceanityEquipmentComponent.h"
#include "Interfaces/CombatInterface.h"

void UOceanityAN_GameplayEventSocketLocation::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotify(BranchingPointPayload);

	APawn* Pawn = Cast<APawn>(BranchingPointPayload.SkelMeshComponent->GetOwner());
	AActor* Actor = Cast<AActor>(Pawn);
	FVector SocketLocation = FVector::ZeroVector;

	if (const ICombatInterface* CombatInterfacePtr = Cast<ICombatInterface>(Pawn))
	{
		SocketLocation = CombatInterfacePtr->GetCombatSocketLocation();
	}

	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.Location = SocketLocation;
	DataHandle.Add(Data);
	
	FGameplayEventData EventData;
	EventData.Instigator = Pawn;
	EventData.Target = Pawn;
	EventData.EventTag = EventTag;
	EventData.TargetData = DataHandle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, EventTag, EventData);
	
}

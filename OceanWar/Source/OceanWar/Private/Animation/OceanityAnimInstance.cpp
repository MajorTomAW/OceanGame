// Copyright © 2023 MajorT. All rights reserved.


#include "Animation/OceanityAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UOceanityAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (TryGetPawnOwner())
	{
		OwnedCharacter = Cast<ACharacter>(TryGetPawnOwner());
	}
}

void UOceanityAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(OwnedCharacter))
	{
		OwnedCharacter = Cast<ACharacter>(TryGetPawnOwner());
	}
	if (!IsValid(OwnedCharacter)) return;

	const FVector Velocity = OwnedCharacter->GetVelocity();
	const FRotator Rotation = OwnedCharacter->GetActorRotation();

	OwnedCharacterRotation = Rotation;
	Speed = UKismetMathLibrary::VSize2D(FVector2d(Velocity.X, Velocity.Y));
	SpeedZ = Velocity.Z;
	Direction = UKismetAnimationLibrary::CalculateDirection(FVector(Velocity.X, Velocity.Y, 0.f), Rotation);
	bIsInAir = OwnedCharacter->GetCharacterMovement()->IsFalling();
}

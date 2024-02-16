// Copyright © 2023 MajorT. All rights reserved.


#include "Animation/PlayerAnimInstance.h"

#include "GameFramework/Character.h"
#include "Ships/OceanityShip.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (const AOceanityShip* PlayerShip = Cast<AOceanityShip>(OwnedCharacter))
	{
		AimPitch = FMath::Clamp(PlayerShip->GetAO_Pitch(), 0.f, 90.f); // The Player should not be able to aim below the ship
		AimYaw = PlayerShip->GetAO_Yaw();
	}
}

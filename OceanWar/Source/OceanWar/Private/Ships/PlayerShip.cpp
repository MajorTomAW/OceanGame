// Copyright © 2023 MajorT. All rights reserved.

#include "Ships/PlayerShip.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HUD/CommonHUD.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerController/OceanityPlayerController.h"
#include "PlayerState/OceanityPlayerState.h"
#include "UI/HUD/OceanityHUD.h"

// Sets default values
APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = 0.f;

	// Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	if (SpringArmComponent)
	{
		SpringArmComponent->SetupAttachment(WeaponSocketMesh, FName("CameraSocket"));
		SpringArmComponent->TargetArmLength = 1000.f;
		SpringArmComponent->TargetOffset = FVector(0.f, 0.f, 100.f);
		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->bInheritPitch = true;
		SpringArmComponent->bInheritYaw = true;
		SpringArmComponent->bInheritRoll = true;
		SpringArmComponent->bDoCollisionTest = false;
	}

	// Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	if (CameraComponent)
	{
		CameraComponent->SetupAttachment(SpringArmComponent);
		CameraComponent->bUsePawnControlRotation = false;
	}
}

void APlayerShip::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddStartupGameplayAbilities();
}

void APlayerShip::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void APlayerShip::InitAbilityActorInfo()
{
	AOceanityPlayerState* OceanityPlayerState = GetPlayerState<AOceanityPlayerState>();
	if (!IsValid(OceanityPlayerState)) return;

	AbilitySystemComponent = OceanityPlayerState->GetAbilitySystemComponent();
	AttributeSet = OceanityPlayerState->GetAttributeSet();
	OceanityPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(OceanityPlayerState, this);

	if (AOceanityPlayerController* OceanityPlayerController = Cast<AOceanityPlayerController>(GetController()))
	{
		if (AOceanityHUD* OceanityHUD = Cast<AOceanityHUD>(OceanityPlayerController->GetHUD()))
		{
			OceanityHUD->InitOverlay();
			OceanityHUD->InitOverlayWithParams(OceanityPlayerController, OceanityPlayerState, AbilitySystemComponent, AttributeSet);
		}
		InitializeAttributes();
	}
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	SpringArmLength = SpringArmComponent->TargetArmLength;
}

void APlayerShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ManageSpringArmLength();
}


void APlayerShip::ManageSpringArmLength()
{
	if (!IsLocallyControlled()) return;
	float CamDistance = 0.f;

	const float AlternativeLength = FMath::Lerp(1500.f, 0.f, ( GetControlRotation().Pitch + 90.f ) / 180.f );

	FHitResult HitResult;
	const FVector Start = SpringArmComponent->GetComponentLocation();
	const FVector End = Start + CameraComponent->GetForwardVector() * SpringArmLength * -1.f;
	TArray<TObjectPtr<AActor>> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	const bool bHit = UKismetSystemLibrary::SphereTraceSingle(
		this,
		Start,
		End,
		20.f,
		UEngineTypes::ConvertToTraceType(ECC_Camera),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true);

	if (bHit)
	{
		const float Distance = UKismetMathLibrary::Vector_Distance(HitResult.ImpactPoint, CameraComponent->GetComponentLocation());
		CamDistance = FMath::Min(Distance, AlternativeLength);
	}
	else
	{
		CamDistance = AlternativeLength;
	}

	// Apply the new Spring Arm Length using interpolation
	SpringArmComponent->TargetArmLength = FMath::FInterpTo<float>(SpringArmComponent->TargetArmLength, ScrollArmLength * CamDistance * MasterArmLength, GetWorld()->GetDeltaSeconds(), 2.5f);
	SpringArmComponent->CameraRotationLagSpeed = FMath::Lerp<float>(100.f, 20.f, ScrollArmLength * MasterArmLength);
	SpringArmComponent->CameraLagSpeed = FMath::Lerp<float>(100.f, 18.f, ScrollArmLength * MasterArmLength);
}

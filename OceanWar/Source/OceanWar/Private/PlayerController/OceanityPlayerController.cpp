// Copyright © 2023 MajorT. All rights reserved.

#include "PlayerController/OceanityPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "RenderGraphResources.h"
#include "AbilitySystem/OceanityAbilityComponent.h"
#include "AbilitySystem/OceanityAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Input/OceanityInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Ships/OceanityShip.h"

AOceanityPlayerController::AOceanityPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AOceanityPlayerController::BindValuesToAttributes()
{
}

void AOceanityPlayerController::SetCurrentVelocity(float NewVelocity)
{
	CurrentVelocity = FMath::Clamp(NewVelocity, -GeneralMaxVelocity, GeneralMaxVelocity);
	InputVelocity = 1.f;
	GetPawn<ACharacter>()->GetCharacterMovement()->MaxWalkSpeed = CurrentVelocity;
}

void AOceanityPlayerController::Client_ShowDamageNumber_Implementation(float DamageAmount,
	const FGameplayTagContainer& DamageTags, ACharacter* TargetCharacter)
{
}


void AOceanityPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AOceanityShip* PawnShip = Cast<AOceanityShip>(GetPawn()))
	{
		PawnShip->OnAbilityActorInfoSetDelegate.AddDynamic(this, &ThisClass::PawnAbilityActorInfoSet);	
	}
	
	checkf(InputMappingContext, TEXT("InputMappingContext is not set in %s"), *GetName());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;

	// Input mode
	FInputModeGameOnly InputModeData;
	InputModeData.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputModeData);
}

void AOceanityPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsValid(GetPawn()))
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), InputVelocity);
	}
}


/** Ability Input Logic */
UOceanityAbilityComponent* AOceanityPlayerController::GetASC()
{
	if (OceanityAbilityComponent == nullptr)
	{
		OceanityAbilityComponent = Cast<UOceanityAbilityComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return OceanityAbilityComponent;
}

void AOceanityPlayerController::AbilityInputTagPressed(FGameplayTag AbilityTag)
{
	// GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("AbilityInputTagPressed for Tag:" + AbilityTag.ToString()));
}

void AOceanityPlayerController::AbilityInputTagReleased(FGameplayTag AbilityTag)
{
	if (!GetASC()) return;
	GetASC()->AbilityInputTagReleased(AbilityTag);
}

void AOceanityPlayerController::AbilityInputTagHeld(FGameplayTag AbilityTag)
{
	if (!GetASC()) return;
	GetASC()->AbilityInputTagHeld(AbilityTag);
}

/** Movement Logic */
void AOceanityPlayerController::StopAcceleratingShip()
{
	AccelerateAxisValue = 0.f;
}

void AOceanityPlayerController::AccelerateShip(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;
	AccelerateAxisValue = Value.Get<float>();
	if (AccelerateAxisValue != 0.f)
	{
		CalculateAcceleration(AccelerateAxisValue);	
	}
}

void AOceanityPlayerController::CalculateAcceleration(float Delta)
{
	//TODO: Make these Values connected to player attributes
	constexpr float BackwardsMultiplier = 0.5f;

	// Calculate velocity
	Delta = Delta * GetWorld()->DeltaTimeSeconds * 100.f * GeneralAcceleration;
	CurrentVelocity = FMath::Clamp(CurrentVelocity + Delta, -GeneralMaxVelocity, GeneralMaxVelocity);

	// Zero Buffer
	if (FMath::Abs(CurrentVelocity) < 20.f)
	{
		InputVelocity = 0.f;
	}
	else
	{
		CurrentVelocity > 0.f ? InputVelocity = 1.f : InputVelocity = -1.f;
	}

	// Apply new max walk speed
	ShipMaxVelocity = FMath::Abs(CurrentVelocity > 0.f ? CurrentVelocity : CurrentVelocity * BackwardsMultiplier);
	GetPawn<ACharacter>()->GetCharacterMovement()->MaxWalkSpeed = ShipMaxVelocity;
	Server_ReplicateMaxVelocity(ShipMaxVelocity);
}

void AOceanityPlayerController::Server_ReplicateMaxVelocity_Implementation(const float& NewMaxVelocity)
{
	ShipMaxVelocity = NewMaxVelocity;
	OnRep_ShipMaxVelocity();
}

void AOceanityPlayerController::OnRep_ShipMaxVelocity()
{
	if (IsValid(GetPawn()))
	{
		GetPawn<ACharacter>()->GetCharacterMovement()->MaxWalkSpeed = ShipMaxVelocity;	
	}
}

void AOceanityPlayerController::TurnShip(const FInputActionValue& Value)
{
	const float InputAxisValue = Value.Get<float>() * GetWorld()->GetDeltaSeconds() * 100.f * GeneralTurnSpeed;
	const FRotator ActorRotation(GetPawn()->GetActorRotation());
	LocalYaw += InputAxisValue;
	const FRotator NewRotation(ActorRotation.Pitch, LocalYaw, ActorRotation.Roll);

	// Rotate the ship and replicate to other clients
	GetPawn()->SetActorRotation(NewRotation);
	Server_ReplicateShipRotation(NewRotation);
}

void AOceanityPlayerController::Server_ReplicateShipRotation_Implementation(const FRotator& NewRotation)
{
	ShipRotation = NewRotation;
	OnRep_ShipRotation();
}

void AOceanityPlayerController::OnRep_ShipRotation()
{
	GetPawn<ACharacter>()->SetActorRotation(ShipRotation);	
}

void AOceanityPlayerController::LookCamera(const FInputActionValue& Value)
{
	constexpr float Multiplier = 1.f;
	const FVector2d InputAxisValue = Value.Get<FVector2d>();
	const float Pitch = FMath::Clamp(InputAxisValue.Y  * Multiplier + GetControlRotation().Pitch, -85.f , 40.f);
	const float Yaw = InputAxisValue.X *  Multiplier + GetControlRotation().Yaw;
	SetControlRotation(FRotator(Pitch, Yaw, 0.f));
}


void AOceanityPlayerController::PawnAbilityActorInfoSet()
{
	if (!GetASC()) return;
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Ability Actor Info Set: %s"), *GetName()), true, true, FLinearColor::Green, 10.f);

	if (AOceanityShip* PawnShip = Cast<AOceanityShip>(GetPawn()))
	{
		UOceanityAttributeSet* AS = Cast<UOceanityAttributeSet>(PawnShip->GetAttributeSet());

		GetASC()->GetGameplayAttributeValueChangeDelegate(AS->GetMaxSpeedAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Max Speed: %f"), Data.NewValue), true, true, FLinearColor::Blue, 10.f);
				GeneralMaxVelocity = Data.NewValue;
			});
		GetASC()->GetGameplayAttributeValueChangeDelegate(AS->GetAccelerationAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Acceleration: %f"), Data.NewValue), true, true, FLinearColor::Blue, 10.f);
				GeneralAcceleration = Data.NewValue;
			});
		GetASC()->GetGameplayAttributeValueChangeDelegate(AS->GetTurnSpeedAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Turn Speed: %f"), Data.NewValue), true, true, FLinearColor::Blue, 10.f);
				GeneralTurnSpeed = Data.NewValue;
			});
	}
}

void AOceanityPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UOceanityInputComponent* OceanityInputComponent = CastChecked<UOceanityInputComponent>(InputComponent))
	{
		OceanityInputComponent->BindAction(AccelerateAction, ETriggerEvent::Triggered, this, &ThisClass::AccelerateShip);
		OceanityInputComponent->BindAction(AccelerateAction, ETriggerEvent::Completed, this, &ThisClass::StopAcceleratingShip);
		OceanityInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::TurnShip);
		OceanityInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::LookCamera);

		OceanityInputComponent->BindAbilityActions(
			InputConfig,
			this,
			&ThisClass::AbilityInputTagPressed,
			&ThisClass::AbilityInputTagReleased,
			&ThisClass::AbilityInputTagHeld);
	}
}

void AOceanityPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AOceanityPlayerController, ShipMaxVelocity, COND_SkipOwner, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AOceanityPlayerController, ShipRotation, COND_SkipOwner, REPNOTIFY_Always);
	DOREPLIFETIME(AOceanityPlayerController, GeneralMaxVelocity);
	DOREPLIFETIME(AOceanityPlayerController, GeneralAcceleration);
	DOREPLIFETIME(AOceanityPlayerController, GeneralTurnSpeed);
	DOREPLIFETIME(AOceanityPlayerController, GeneralWeight);
}


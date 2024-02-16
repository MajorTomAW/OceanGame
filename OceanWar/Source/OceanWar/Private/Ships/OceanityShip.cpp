// Copyright © 2023 MajorT. All rights reserved.

#include "Ships/OceanityShip.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystem/FunctionLibraries/OceanityAbilityFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "OceanWar/OceanWar.h"

// Sets default values
AOceanityShip::AOceanityShip()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(false);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Weapon Socket Mesh
	WeaponSocketMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSocketMesh"));
	if (WeaponSocketMesh)
	{
		WeaponSocketMesh->SetupAttachment(GetMesh(), FName("WeaponSocketMeshSocket"));
		WeaponSocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	}
	
	// Weapon Mesh
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	if (WeaponMesh)
	{
		WeaponMesh->AlwaysLoadOnClient = true;
		WeaponMesh->AlwaysLoadOnServer = true;
		WeaponMesh->bOwnerNoSee = false;
		WeaponMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		WeaponMesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMesh->SetupAttachment(WeaponSocketMesh, FName("WeaponMeshSocket"));
	}

	// Engine Mesh
	EngineMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EngineMesh"));
	if (EngineMesh)
	{
		EngineMesh->SetupAttachment(GetMesh(), FName("EngineMeshSocket"));
		EngineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	}
}

void AOceanityShip::Multicast_HandleDeath_Implementation()
{
	WeaponSocketMesh->SetSimulatePhysics(true);
	WeaponSocketMesh->SetEnableGravity(true);
	WeaponSocketMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	WeaponSocketMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	WeaponMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	EngineMesh->SetSimulatePhysics(true);
	EngineMesh->SetEnableGravity(true);
	EngineMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	EngineMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}
void AOceanityShip::AimOffset(float DeltaTime)
{
	AO_Yaw = GetBaseAimRotation().Yaw;
	AO_Pitch = GetBaseAimRotation().Pitch;

	if (AO_Pitch > 90.f && !IsLocallyControlled())
	{
		// map pitch from [270, 360) to [-90, 0)
		const FVector2D InRange(270.f, 360.f);
		const FVector2D OutRange(-90.f, 0.f);
		AO_Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AO_Pitch);
	}
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("AO_Yaw: %f"), AO_Yaw), true, true, FLinearColor::Red, 0.f, FName("Yaw"));
}

void AOceanityShip::InitAbilityActorInfo()
{
}

void AOceanityShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimOffset(DeltaSeconds);
}

void AOceanityShip::AddStartupGameplayAbilities() const
{
	if (AbilitySystemComponent)
	{
		UOceanityAbilityFunctionLibrary::AddStartupAbilities(
			this,
			TurretClass,
			EngineClass,
			HullClass,
			AbilitySystemComponent
			);
	}
}

void AOceanityShip::InitializeAttributes() const
{
	if (AbilitySystemComponent)
	{
		UOceanityAbilityFunctionLibrary::InitializeDefaultAttribute(
			this,
			TurretClass,
			EngineClass,
			HullClass,
			AbilitySystemComponent
			);
	}
}

void AOceanityShip::BeginPlay()
{
	Super::BeginPlay();
	if (GetMesh())
	{
		DynamicHullMaterialInstance = GetMesh()->CreateDynamicMaterialInstance(0, HullMaterialInstance);
	}
}


void AOceanityShip::InitializeSpecificAttribute(TSubclassOf<UGameplayEffect> InGameplayEffect, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(InGameplayEffect);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InGameplayEffect, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

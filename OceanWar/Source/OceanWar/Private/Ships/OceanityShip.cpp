// Copyright © 2023 MajorT. All rights reserved.

#include "Ships/OceanityShip.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystem/OceanityAttributeSet.h"
#include "AbilitySystem/FunctionLibraries/OceanityAbilityFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "OceanWar/OceanWar.h"
#include "PlayerController/OceanityPlayerController.h"

// Sets default values
AOceanityShip::AOceanityShip()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(false);
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(2);
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
		WeaponSocketMesh->SetRenderCustomDepth(true);
		WeaponSocketMesh->SetCustomDepthStencilValue(2);
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
		WeaponMesh->SetRenderCustomDepth(true);
		WeaponMesh->SetCustomDepthStencilValue(2);
	}

	// Engine Mesh
	EngineMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EngineMesh"));
	if (EngineMesh)
	{
		EngineMesh->SetupAttachment(GetMesh(), FName("EngineMeshSocket"));
		EngineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		EngineMesh->SetRenderCustomDepth(true);
		EngineMesh->SetCustomDepthStencilValue(2);
	}

	// Equipment Component
	EquipmentComponent = CreateDefaultSubobject<UOceanityEquipmentComponent>(TEXT("EquipmentComponent"));
	if (EquipmentComponent)
	{
		// EquipmentComponent->SetIsReplicated(true);
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
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("AO_Yaw: %f"), AO_Yaw), true, true, FLinearColor::Red, 0.f, FName("Yaw"));
}

void AOceanityShip::BindFunctionsToEquipmentComponent()
{
	if (IsValid(EquipmentComponent))
	{
		//EquipmentComponent->BindEquipmentActions(this, &AOceanityShip::OnTurretMeshChanged, &AOceanityShip::OnEngineMeshChanged, &AOceanityShip::OnHullMeshChanged);
		EquipmentComponent->OnTurretMeshChanged.AddDynamic(this, &AOceanityShip::OnTurretMeshChanged);
		EquipmentComponent->OnEngineMeshChanged.AddDynamic(this, &AOceanityShip::OnEngineMeshChanged);
		EquipmentComponent->OnHullMeshChanged.AddDynamic(this, &AOceanityShip::OnHullMeshChanged);
	}
}

void AOceanityShip::OnTurretMeshChanged(USkeletalMesh* NewMesh)
{
	WeaponMesh->SetSkeletalMesh(NewMesh);
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Turret Mesh Changed: %s"), *NewMesh->GetName()), true, true, FLinearColor::Red, 2.f, FName("Turret"));
}

void AOceanityShip::OnEngineMeshChanged(USkeletalMesh* NewMesh)
{
	EngineMesh->SetSkeletalMesh(NewMesh);
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Engine Mesh Changed: %s"), *NewMesh->GetName()), true, true, FLinearColor::Red, 2.f, FName("Engine"));
}

void AOceanityShip::OnHullMeshChanged(USkeletalMesh* NewMesh)
{
	GetMesh()->SetSkeletalMesh(NewMesh);
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Hull Mesh Changed: %s"), *NewMesh->GetName()), true, true, FLinearColor::Red, 2.f, FName("Hull"));
}


/** Combat Interface */
UAnimMontage* AOceanityShip::GetWeaponMontage() const
{
	if (IsValid(EquipmentComponent))
	{
		return EquipmentComponent->GetAttackMontage();
	}
	return nullptr;
}
/** End Combat Interface */

void AOceanityShip::InitAbilityActorInfo()
{
	AbilityActorInfoSet();
}

void AOceanityShip::AbilityActorInfoSet()
{
	/*if (const UOceanityAttributeSet* AS = Cast<UOceanityAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxSpeedAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Max Speed: %f"), Data.NewValue), true, true, FLinearColor::Blue, 10.f);
			});
	}*/
	OnAbilityActorInfoSetDelegate.Broadcast();

	if (AOceanityPlayerController* PC = Cast<AOceanityPlayerController>(GetController()))
	{
		PC->PawnAbilityActorInfoSet();
	}
}

void AOceanityShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimOffset(DeltaSeconds);
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

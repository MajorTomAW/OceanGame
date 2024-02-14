// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/Actor/OceanityProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "OceanWar/OceanWar.h"


// Sets default values
AOceanityProjectile::AOceanityProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ProjectileHitboxComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	if (ProjectileHitboxComponent)
	{
		SetRootComponent(ProjectileHitboxComponent);
		ProjectileHitboxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		ProjectileHitboxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		ProjectileHitboxComponent->SetCollisionObjectType(ECC_Projectile);
		ProjectileHitboxComponent->SetCollisionResponseToChannel(ECC_Hitbox, ECR_Overlap);
	}

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	if (ProjectileMeshComponent)
	{
		ProjectileMeshComponent->SetupAttachment(ProjectileHitboxComponent);
		ProjectileMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	ObjectHitboxComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Object Hitbox"));
	if (ObjectHitboxComponent)
	{
		ObjectHitboxComponent->SetupAttachment(ProjectileMeshComponent);
		ObjectHitboxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		ObjectHitboxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		ObjectHitboxComponent->SetCollisionObjectType(ECC_WorldDynamic);
		ObjectHitboxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
		ObjectHitboxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->InitialSpeed = 1500.f;
		ProjectileMovementComponent->MaxSpeed = 1500.f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->ProjectileGravityScale = .5f;
	}
}

void AOceanityProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	ProjectileHitboxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
	ObjectHitboxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnObjectCollisionOverlap);
}

void AOceanityProjectile::Destroyed()
{
	Super::Destroyed();
	if (!bHit && !HasAuthority())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffectWater, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}
}

void AOceanityProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || OtherActor == GetOwner() || OtherActor == GetInstigator()) return;
	
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffectShip, GetActorLocation());

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

void AOceanityProjectile::OnObjectCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || OtherActor == GetOwner() || OtherActor == GetInstigator()) return;

	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffectObject, GetActorLocation());

	if (HasAuthority())
	{
		Destroy();
	}
}


// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/Actor/OceanityProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "OceanityGameplayTags.h"
#include "Components/AudioComponent.h"
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
	
	PlayImpactSound(1);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffectShip, GetActorLocation());

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			FGameplayEffectContextHandle Context = DamageEffectSpecHandle.Data->GetContext();
			FHitResult HitResult;
			HitResult.TraceStart = GetActorLocation();
			HitResult.TraceEnd = OtherActor->GetActorLocation();
			Context.AddHitResult(HitResult);
			DamageEffectSpecHandle.Data->SetContext(Context);
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());

			/*
			 * Send Gameplay Event to the target
			 */
			FGameplayEventData EventData;
			EventData.Target = OtherActor;
			EventData.Instigator = GetInstigator();
			EventData.ContextHandle = Context;
			
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, FOceanityGameplayTags::Get().Ability_Event_HitReact, EventData);

			FGameplayEventData HitEventData;
			HitEventData.Instigator = GetInstigator();
			HitEventData.Target = OtherActor;
			HitEventData.ContextHandle = Context;
			HitEventData.EventTag = FOceanityGameplayTags::Get().GameplayEvent_Hit_Success;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, FOceanityGameplayTags::Get().GameplayEvent_Hit_Success, HitEventData);
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
	PlayImpactSound(0);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffectObject, GetActorLocation());

	if (HasAuthority())
	{
		Destroy();
	}
}

void AOceanityProjectile::PlayImpactSound(uint8 ImpactIndex) const
{
	if (UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, ImpactSound, GetActorLocation()))
	{
		AudioComponent->SetIntParameter(FName("Impact Index"), ImpactIndex);
		AudioComponent->Play();
	}
}


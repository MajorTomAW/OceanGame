// Copyright © 2023 MajorT. All rights reserved.


#include "Actor/CommonEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "CommonAbilitySystem.h"
#include "Components/SphereComponent.h"


// Sets default values
ACommonEffectActor::ACommonEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	if (OverlapSphere)
	{
		OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		OverlapSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
		OverlapSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		RootComponent = OverlapSphere;
	}
}

void ACommonEffectActor::BeginPlay()
{
	Super::BeginPlay();
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}

void ACommonEffectActor::ApplyEffectToTarget(AActor* Target, const FGameplayEffectApplication& InEffect)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (!IsValid(ASC)) return;

	checkf(InEffect.GameplayEffectClass, TEXT("GameplayEffectClass is nullptr"));
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(InEffect.GameplayEffectClass, InEffect.Level, ContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	if (EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, ASC);
	}
}

void ACommonEffectActor::RemoveEffectFromTarget(AActor* Target, const FGameplayEffectApplication& InEffect)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (!IsValid(ASC)) return;

	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	for (const auto& Pair : ActiveEffectHandles)
	{
		if (ASC == Pair.Value)
		{
			ASC->RemoveActiveGameplayEffect(Pair.Key, 1);
			HandlesToRemove.Add(Pair.Key);
		}
	}
	for (const FActiveGameplayEffectHandle& Handle : HandlesToRemove)
	{
		ActiveEffectHandles.Remove(Handle);
	}
}

void ACommonEffectActor::HandleTargetOverlapped(AActor* Target)
{
	for (const FGameplayEffectApplication& EffectApplication : AppliedEffects)
	{
		if (EffectApplication.ApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap)
		{
			ApplyEffectToTarget(Target, EffectApplication);
		}
	}
}

void ACommonEffectActor::HandleTargetEndOverlapped(AActor* Target)
{
	for (const FGameplayEffectApplication& EffectApplication : AppliedEffects)
	{
		if (EffectApplication.ApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlapEnd)
		{
			ApplyEffectToTarget(Target, EffectApplication);
		}
		else if (EffectApplication.RemovalPolicy == EEffectRemovalPolicy::ERP_RemoveOnOverlapEnd)
		{
			RemoveEffectFromTarget(Target, EffectApplication);
		}
	}
}

void ACommonEffectActor::OnOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const bool bIsEnemy = OtherActor->ActorHasTag(Tag_Enemy);
	if (bApplyToNonPlayers && bIsEnemy) return;

	HandleTargetOverlapped(OtherActor);
	if (bDestroyActorOnOverlapEnd)
	{
		Destroy();
	}
}

void ACommonEffectActor::OnEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const bool bIsEnemy = OtherActor->ActorHasTag(Tag_Enemy);
	if (bApplyToNonPlayers && bIsEnemy) return;
	
	HandleTargetEndOverlapped(OtherActor);
	if (bDestroyActorOnOverlapEnd)
	{
		Destroy();
	}
}
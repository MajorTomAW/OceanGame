// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/Abilities/OceanityProjectileAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "OceanityGameplayTags.h"
#include "AbilitySystem/OceanityAttributeSet.h"
#include "AbilitySystem/Actor/OceanityProjectile.h"
#include "Interfaces/CombatInterface.h"


void UOceanityProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UOceanityProjectileAbility::SpawnProjectile(float PitchOffset)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());

		if (const APawn* Pawn = Cast<APawn>(GetAvatarActorFromActorInfo()))
		{
			FRotator AimRotation = Pawn->GetBaseAimRotation();
			AimRotation.Pitch += PitchOffset;
			SpawnTransform.SetRotation(AimRotation.Quaternion());

			AOceanityProjectile* Projectile = GetWorld()->SpawnActorDeferred<AOceanityProjectile>(
				ProjectileClass,
				SpawnTransform,
				GetAvatarActorFromActorInfo(),
				Cast<APawn>(GetAvatarActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
				);


			//TODO: Add damage
			if (UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo()))
			{
				FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
				ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
				const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, .1, ContextHandle);
				float Damage = 0.f;
				if (const UOceanityAttributeSet* AS = Cast<UOceanityAttributeSet>(SourceASC->GetAttributeSet(UOceanityAttributeSet::StaticClass())))
				{
					Damage = AS->GetDamage();
				}
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FOceanityGameplayTags::Get().Attributes_Primary_Damage, Damage);
				Projectile->DamageEffectSpecHandle = SpecHandle;
			}
			
			Projectile->FinishSpawning(SpawnTransform);
		}
	}
}
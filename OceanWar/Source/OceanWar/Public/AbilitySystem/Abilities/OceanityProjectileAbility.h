// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameplayAbility.h"
#include "OceanityProjectileAbility.generated.h"

class AOceanityProjectile;
/**
 * 
 */
UCLASS()
class OCEANWAR_API UOceanityProjectileAbility : public UCommonGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AOceanityProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(float PitchOffset);
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};

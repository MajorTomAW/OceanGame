// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "OceanityProjectile.generated.h"

class UNiagaraSystem;

UCLASS(Abstract)
class OCEANWAR_API AOceanityProjectile : public AActor
{
	GENERATED_BODY()

public:
	AOceanityProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USphereComponent> ProjectileHitboxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCapsuleComponent> ObjectHitboxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ProjectileMeshComponent;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnObjectCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool bHit = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Particles")
	TObjectPtr<UNiagaraSystem> ImpactEffectWater;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Particles")
	TObjectPtr<UNiagaraSystem> ImpactEffectObject;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Particles")
	TObjectPtr<UNiagaraSystem> ImpactEffectShip;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Sounds")
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Life")
	float LifeSpan = 60.f;
};

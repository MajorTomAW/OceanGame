// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommonEffectActor.generated.h"

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	EAP_ApplyOnOverlap UMETA(DisplayName = "Apply On Overlap"),
	EAP_ApplyOnOverlapEnd UMETA(DisplayName = "Apply On Overlap End"),
	EAP_DoNotApply UMETA(DisplayName = "Do Not Apply")
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	ERP_RemoveOnOverlapEnd UMETA(DisplayName = "Remove On Overlap End"),
	ERP_DoNotRemove UMETA(DisplayName = "Do Not Remove")
};

USTRUCT(BlueprintType)
struct FGameplayEffectApplication
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> GameplayEffectClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Level = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EEffectApplicationPolicy ApplicationPolicy = EEffectApplicationPolicy::EAP_ApplyOnOverlap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EEffectRemovalPolicy RemovalPolicy = EEffectRemovalPolicy::ERP_RemoveOnOverlapEnd;
};

UCLASS()
class COMMONABILITYSYSTEM_API ACommonEffectActor : public AActor
{
	GENERATED_BODY()

public:
	ACommonEffectActor();

protected:
	virtual void BeginPlay() override;

	/** User Params */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Common|Effects")
	TArray<FGameplayEffectApplication> AppliedEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Common|Effects")
	bool bApplyToNonPlayers = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Common|Effects")
	bool bDestroyActorOnOverlapEnd = true;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(UPARAM(DisplayName = "Target Actor") AActor* Target, const FGameplayEffectApplication& InEffect);

	UFUNCTION(BlueprintCallable)
	void RemoveEffectFromTarget(UPARAM(DisplayName = "Target Actor") AActor* Target, const FGameplayEffectApplication& InEffect);

	UFUNCTION(BlueprintCallable)
	void HandleTargetOverlapped(UPARAM(DisplayName = "Target Actor") AActor* Target);

	UFUNCTION(BlueprintCallable)
	void HandleTargetEndOverlapped(UPARAM(DisplayName = "Target Actor") AActor* Target);

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "On Target Overlapped"))
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "On Target End Overlapped"))
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> OverlapSphere;

	TMap<struct FActiveGameplayEffectHandle, class UAbilitySystemComponent*> ActiveEffectHandles;
};

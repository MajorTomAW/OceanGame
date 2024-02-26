// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "OceanityPlayerController.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UOceanityAbilityComponent;

/**
 * 
 */
UCLASS()
class OCEANWAR_API AOceanityPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AOceanityPlayerController();

	UFUNCTION(BlueprintCallable)
	void SetCurrentVelocity(float NewVelocity);

	UFUNCTION(Client, Reliable)
	void Client_ShowDamageNumber(float DamageAmount, const FGameplayTagContainer& DamageTags, ACharacter* TargetCharacter);

	UFUNCTION()
	void PawnAbilityActorInfoSet();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void BindValuesToAttributes();
	
	UPROPERTY(EditDefaultsOnly, Category = "Input|EnhancedInput")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input|EnhancedInput")
	TObjectPtr<UInputAction> AccelerateAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input|EnhancedInput")
	TObjectPtr<UInputAction> TurnAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input|EnhancedInput")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UAbilityInputConfig> InputConfig;

	/** Ability Input Logic */
	UPROPERTY()
	TObjectPtr<UOceanityAbilityComponent> OceanityAbilityComponent;

	UOceanityAbilityComponent* GetASC();
	
	void AbilityInputTagPressed(FGameplayTag AbilityTag);
	void AbilityInputTagReleased(FGameplayTag AbilityTag);
	void AbilityInputTagHeld(FGameplayTag AbilityTag);
	/** end Ability Input Logic */
	
	/** Movement Logic */
	void AccelerateShip(const FInputActionValue& Value);
	void StopAcceleratingShip();
	void TurnShip(const FInputActionValue& Value);
	void LookCamera(const FInputActionValue& Value);
	void CalculateAcceleration(float Delta);

	/** Movement values */
	float AccelerateAxisValue = 0.f;
	float LocalYaw = 0.f;
	float CurrentVelocity = 0.f;
	float InputVelocity = 0.f;

	UPROPERTY(Replicated)
	float GeneralMaxVelocity = 600.f;

	UPROPERTY(Replicated)
	float GeneralAcceleration = 2.f;

	UPROPERTY(Replicated)
	float GeneralTurnSpeed = 0.5f;

	UPROPERTY(Replicated)
	float GeneralWeight = 0.f;

	UPROPERTY(ReplicatedUsing = OnRep_ShipMaxVelocity)
	float ShipMaxVelocity = 0.f;

	UPROPERTY(ReplicatedUsing = OnRep_ShipRotation)
	FRotator ShipRotation;
	
	UFUNCTION(Server, Reliable)
	void Server_ReplicateShipRotation(const FRotator& NewRotation);

	UFUNCTION(Server, Reliable)
	void Server_ReplicateMaxVelocity(const float& NewMaxVelocity);
	
	UFUNCTION()
	void OnRep_ShipMaxVelocity();

	UFUNCTION()
	void OnRep_ShipRotation();
	/** end Movement Logic */
};

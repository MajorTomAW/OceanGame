// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OceanityPlayerController.generated.h"

struct FGameplayTagContainer;
class UAbilitySystemComponent;
struct FGameplayTag;
class UAttributeSet;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

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

	float GeneralMaxVelocity = 600.f;
	float GeneralAcceleration = 2.f;
	float GeneralTurnSpeed = 0.5f;
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

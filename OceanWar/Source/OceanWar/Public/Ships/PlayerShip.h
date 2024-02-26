// Copyright © 2023 MajorT. All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ships/OceanityShip.h"
#include "PlayerShip.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class OCEANWAR_API APlayerShip : public AOceanityShip
{
	GENERATED_BODY()

public:
	APlayerShip();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetMasterArmLength(float InMasterArmLength) {MasterArmLength = InMasterArmLength;}

	UFUNCTION(BlueprintCallable)
	void SetScrollArmLength(float InScrollArmLength) {ScrollArmLength = InScrollArmLength;}

	UFUNCTION(BlueprintPure)
	float GetScrollArmLength() const {return ScrollArmLength;}

	UPROPERTY(BlueprintReadWrite)
	bool bInScope = false;

protected:
	virtual void InitAbilityActorInfo() override;

	virtual void ManageEnemyHealthBarVisibility(bool bVisible, UWidgetComponent* WidgetComponent) override;

	UFUNCTION(Client, Reliable)
	void ClientManageEnemyHealthBarVisibility(bool bVisible, UWidgetComponent* WidgetComponent);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

private:
	
	// Camera
	float SpringArmLength = 0.f;
	float ScrollArmLength = 1.f;
	float MasterArmLength = 1.f;

	void ManageSpringArmLength();

};

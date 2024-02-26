// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "OceanityShip.h"
#include "UI/Controller/AttributeWidgetController.h"
#include "AIShip.generated.h"

class APlayerShip;
class UWidgetComponent;

UCLASS()
class OCEANWAR_API AAIShip : public AOceanityShip
{
	GENERATED_BODY()

public:
	AAIShip();

	FValueChangedSignature OnAttributeValueChangedDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void BindToAttributeDelegates();
	virtual void BroadcastInitialAttributes();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UWidgetComponent> HealthBarWidgetComponent;

private:
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	UFUNCTION()
	void ManageWidgetComponentVisibility() const;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetComponent")
	float MaxWidgetDrawDistance = 4000.f;
};

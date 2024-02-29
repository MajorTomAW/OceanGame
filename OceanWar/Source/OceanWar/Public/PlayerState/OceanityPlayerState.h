// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "OceanityPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerValueChangedSignature, int32 /* New Value */, int32 /*Old Value */);

/**
 * 
 */
UCLASS()
class OCEANWAR_API AOceanityPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AOceanityPlayerState();

	/** Ability System Interface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	/** End Ability System Interface */

	FORCEINLINE int32 GetCoins() const { return Coins; }
	void AddCoins(int32 InCoins);
	void SetCoins(int32 InCoins);
	FPlayerValueChangedSignature OnCoinsChanged;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/** Ability System */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Coins, Category = "PlayerState")
	int32 Coins = 0;

	UFUNCTION()
	void OnRep_Coins(int32 OldCoins);
};

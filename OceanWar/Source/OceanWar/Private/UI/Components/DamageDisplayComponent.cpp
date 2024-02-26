// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Components/DamageDisplayComponent.h"

#include "UI/Widgets/OverallDamageDisplay.h"


UDamageDisplayComponent::UDamageDisplayComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDamageDisplayComponent::DisplayDamage(float DamageAmount, FGameplayTagContainer DamageTags) const
{
	if (UOverallDamageDisplay* DamageWidget = Cast<UOverallDamageDisplay>(GetUserWidgetObject()))
	{
		DamageWidget->DisplayDamage(DamageAmount, DamageTags);
	}
}

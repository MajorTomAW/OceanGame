// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
 * Gameplay Tags
 *
 * Singleton class that holds all the native Gameplay Tags used in the game.
 */

struct FOceanityGameplayTags
{
 static const FOceanityGameplayTags& Get()
 {
  return GameplayTags;
 }
 static void InitializeNativeGameplayTags();

 /*
  * Gameplay Tags
  */
 /** Vital Attribute Tags */
 FGameplayTag Attributes_Vital_Health;
 FGameplayTag Attributes_Vital_MaxHealth;
 FGameplayTag Attributes_Vital_Shield;
 FGameplayTag Attributes_Vital_MaxShield;

 /** Primary Attribute Tags */
 FGameplayTag Attributes_Primary_Damage;
 FGameplayTag Attributes_Primary_Ammo;
 FGameplayTag Attributes_Primary_MaxAmmo;
 FGameplayTag Attributes_Primary_ReloadSpeed;
 FGameplayTag Attributes_Primary_ShootCooldown;

 /** Secondary Attribute Tags */
 FGameplayTag Attributes_Secondary_MaxSpeed;
 FGameplayTag Attributes_Secondary_Acceleration;
 FGameplayTag Attributes_Secondary_TurnSpeed;
 FGameplayTag Attributes_Secondary_Weight;
 FGameplayTag Attributes_Secondary_BackwardsMultiplier;

 /** Boost Attribute Tags */
 FGameplayTag Attributes_Boost_Duration;
 FGameplayTag Attributes_Boost_Cooldown;
 FGameplayTag Attributes_Boost_Speed;

 /** Damage Tags */
 FGameplayTag Damage_DamageType_Shield;
 FGameplayTag Damage_DamageType_Shield_Destroyed;
 FGameplayTag Damage_DamageType_Health;
 FGameplayTag Damage_DamageType_Health_Dead;

 /** Gameplay Events */
 FGameplayTag GameplayEvent_Hit_Success;
 FGameplayTag GameplayEvent_Hit_Fail;
 FGameplayTag GameplayEvent_Ability_Shoot;

 /** Ability Tags */
 // Events
 FGameplayTag Ability_Event_ShipSunk;
 FGameplayTag Ability_Event_HitReact;
 FGameplayTag Ability_Event_Knockback;


private:
 static FOceanityGameplayTags GameplayTags;
};
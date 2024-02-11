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


 /** Input Tags */
 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;
 FGameplayTag InputTag_1;
 FGameplayTag InputTag_2;
 FGameplayTag InputTag_3;
 FGameplayTag InputTag_4;
 FGameplayTag InputTag_5;


 /** Ability Tags */
 // Descriptor
 FGameplayTag Ability_Descriptor_Melee;
 FGameplayTag Ability_Descriptor_Melee_Launch;
 FGameplayTag Ability_Descriptor_Ranged;
 FGameplayTag Ability_Descriptor_Ranged_Shoot;
 FGameplayTag Ability_Descriptor_Boost;
 FGameplayTag Ability_Descriptor_Reload_Ammo;
 // Events
 FGameplayTag Ability_Event_ShipSunk;
 FGameplayTag Ability_Event_HitReact;
 FGameplayTag Ability_Event_Knockback;
 // Cooldowns
 FGameplayTag Ability_Cooldown_Boost;
 FGameplayTag Ability_Cooldown_Ranged_Shoot;
 FGameplayTag Ability_Cooldown_Melee_Launch;


private:
 static FOceanityGameplayTags GameplayTags;
};
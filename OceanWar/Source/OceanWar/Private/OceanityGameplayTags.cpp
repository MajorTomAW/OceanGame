// Copyright © 2024 MajorT. All rights reserved.


#include "OceanityGameplayTags.h"
#include "GameplayTagsManager.h"

FOceanityGameplayTags FOceanityGameplayTags::GameplayTags;

void FOceanityGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();

	/** Vital Attribute Tags */
	GameplayTags.Attributes_Vital_Health = TagsManager.AddNativeGameplayTag(FName("Attributes.Vital.Health"), TEXT("Amount of health"));
	GameplayTags.Attributes_Vital_MaxHealth = TagsManager.AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"), TEXT("Maximum amount of health"));
	GameplayTags.Attributes_Vital_Shield = TagsManager.AddNativeGameplayTag(FName("Attributes.Vital.Shield"), TEXT("Amount of shield"));
	GameplayTags.Attributes_Vital_MaxShield = TagsManager.AddNativeGameplayTag(FName("Attributes.Vital.MaxShield"), TEXT("Maximum amount of shield"));

	/** Primary Attribute Tags */
	GameplayTags.Attributes_Primary_Damage = TagsManager.AddNativeGameplayTag(FName("Attributes.Primary.Damage"), TEXT("Damage"));
	GameplayTags.Attributes_Primary_Ammo = TagsManager.AddNativeGameplayTag(FName("Attributes.Primary.Ammo"), TEXT("Amount of ammo"));
	GameplayTags.Attributes_Primary_MaxAmmo = TagsManager.AddNativeGameplayTag(FName("Attributes.Primary.MaxAmmo"), TEXT("Maximum amount of ammo"));
	GameplayTags.Attributes_Primary_ReloadSpeed = TagsManager.AddNativeGameplayTag(FName("Attributes.Primary.ReloadSpeed"), TEXT("Reload speed"));
	GameplayTags.Attributes_Primary_ShootCooldown = TagsManager.AddNativeGameplayTag(FName("Attributes.Primary.ShootCooldown"), TEXT("Shoot cooldown"));

	/** Secondary Attribute Tags */
	GameplayTags.Attributes_Secondary_MaxSpeed = TagsManager.AddNativeGameplayTag(FName("Attributes.Secondary.MaxSpeed"), TEXT("Maximum speed"));
	GameplayTags.Attributes_Secondary_Acceleration = TagsManager.AddNativeGameplayTag(FName("Attributes.Secondary.Acceleration"), TEXT("Acceleration"));
	GameplayTags.Attributes_Secondary_TurnSpeed = TagsManager.AddNativeGameplayTag(FName("Attributes.Secondary.TurnSpeed"), TEXT("Turn speed"));
	GameplayTags.Attributes_Secondary_Weight = TagsManager.AddNativeGameplayTag(FName("Attributes.Secondary.Weight"), TEXT("Weight"));
	GameplayTags.Attributes_Secondary_BackwardsMultiplier = TagsManager.AddNativeGameplayTag(FName("Attributes.Secondary.BackwardsMultiplier"), TEXT("Backwards multiplier"));

	/** Boost Attribute Tags */
	GameplayTags.Attributes_Boost_Duration = TagsManager.AddNativeGameplayTag(FName("Attributes.Boost.Duration"), TEXT("Boost duration"));
	GameplayTags.Attributes_Boost_Cooldown = TagsManager.AddNativeGameplayTag(FName("Attributes.Boost.Cooldown"), TEXT("Boost cooldown"));
	GameplayTags.Attributes_Boost_Speed = TagsManager.AddNativeGameplayTag(FName("Attributes.Boost.Speed"), TEXT("Boost speed"));

	/** Input Tags */
	GameplayTags.InputTag_LMB = TagsManager.AddNativeGameplayTag(FName("Input.InputTag.LMB"), TEXT("Left mouse button"));
	GameplayTags.InputTag_RMB = TagsManager.AddNativeGameplayTag(FName("Input.InputTag.RMB"), TEXT("Right mouse button"));
	GameplayTags.InputTag_1 = TagsManager.AddNativeGameplayTag(FName("Input.InputTag.1"), TEXT("1"));
	GameplayTags.InputTag_2 = TagsManager.AddNativeGameplayTag(FName("Input.InputTag.2"), TEXT("2"));
	GameplayTags.InputTag_3 = TagsManager.AddNativeGameplayTag(FName("Input.InputTag.3"), TEXT("3"));
	GameplayTags.InputTag_4 = TagsManager.AddNativeGameplayTag(FName("Input.InputTag.4"), TEXT("4"));
	GameplayTags.InputTag_5 = TagsManager.AddNativeGameplayTag(FName("Input.InputTag.5"), TEXT("5"));

	/** Ability Tags */
	// Ability Descriptors
	GameplayTags.Ability_Descriptor_Melee = TagsManager.AddNativeGameplayTag(FName("Ability.Descriptor.Melee"), TEXT("Melee Ability"));
	GameplayTags.Ability_Descriptor_Ranged = TagsManager.AddNativeGameplayTag(FName("Ability.Descriptor.Ranged"), TEXT("Ranged Ability"));
	GameplayTags.Ability_Descriptor_Boost = TagsManager.AddNativeGameplayTag(FName("Ability.Descriptor.Boost"), TEXT("Boost Ability"));
	GameplayTags.Ability_Descriptor_Melee_Launch = TagsManager.AddNativeGameplayTag(FName("Ability.Descriptor.Melee.Launch"), TEXT("Launch Melee Ability"));
	GameplayTags.Ability_Descriptor_Ranged_Shoot = TagsManager.AddNativeGameplayTag(FName("Ability.Descriptor.Ranged.Shoot"), TEXT("Shoot Ranged Ability"));
	GameplayTags.Ability_Descriptor_Reload_Ammo = TagsManager.AddNativeGameplayTag(FName("Ability.Descriptor.Reload.Ammo"), TEXT("Reload Ammo Ability"));
	// Ability Events
	GameplayTags.Ability_Event_ShipSunk = TagsManager.AddNativeGameplayTag(FName("Ability.Event.ShipSunk"), TEXT("Ship Sunk Event"));
	GameplayTags.Ability_Event_HitReact = TagsManager.AddNativeGameplayTag(FName("Ability.Event.HitReact"), TEXT("Hit React Event"));
	GameplayTags.Ability_Event_Knockback = TagsManager.AddNativeGameplayTag(FName("Ability.Event.Knockback"), TEXT("Knockback Event"));
	// Ability Cooldowns
	GameplayTags.Ability_Cooldown_Boost = TagsManager.AddNativeGameplayTag(FName("Ability.Cooldown.Boost"), TEXT("Boost Cooldown"));
	GameplayTags.Ability_Cooldown_Ranged_Shoot = TagsManager.AddNativeGameplayTag(FName("Ability.Cooldown.Ranged.Shoot"), TEXT("Ranged Shoot Cooldown"));
	GameplayTags.Ability_Cooldown_Melee_Launch = TagsManager.AddNativeGameplayTag(FName("Ability.Cooldown.Melee.Launch"), TEXT("Melee Launch Cooldown"));
	
}

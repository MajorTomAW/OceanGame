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

	/** Damage Tags */
	GameplayTags.Damage_DamageType_Health = TagsManager.AddNativeGameplayTag(FName("Damage.DamageType.Health"), TEXT("Health Damage Type"));
	GameplayTags.Damage_DamageType_Health_Dead = TagsManager.AddNativeGameplayTag(FName("Damage.DamageType.Health.Dead"), TEXT("Dead Health Damage Type"));
	GameplayTags.Damage_DamageType_Shield = TagsManager.AddNativeGameplayTag(FName("Damage.DamageType.Shield"), TEXT("Shield Damage Type"));
	GameplayTags.Damage_DamageType_Shield_Destroyed = TagsManager.AddNativeGameplayTag(FName("Damage.DamageType.Shield.Destroyed"), TEXT("Destroyed Shield Damage Type"));
	

	/** Gameplay Event Tags */
	GameplayTags.GameplayEvent_Hit_Success = TagsManager.AddNativeGameplayTag(FName("GameplayEvent.Hit.Success"), TEXT("Hit Success Event"));
	GameplayTags.GameplayEvent_Hit_Fail = TagsManager.AddNativeGameplayTag(FName("GameplayEvent.Hit.Fail"), TEXT("Hit Fail Event"));
	GameplayTags.GameplayEvent_Ability_Shoot = TagsManager.AddNativeGameplayTag(FName("GameplayEvent.Ability.Shoot"), TEXT("Shoot Ability Event"));
	
	/** Ability Tags */
	// Ability Events
	GameplayTags.Ability_Event_ShipSunk = TagsManager.AddNativeGameplayTag(FName("Ability.Event.ShipSunk"), TEXT("Ship Sunk Event"));
	GameplayTags.Ability_Event_HitReact = TagsManager.AddNativeGameplayTag(FName("Ability.Event.HitReact"), TEXT("Hit React Event"));
	GameplayTags.Ability_Event_Knockback = TagsManager.AddNativeGameplayTag(FName("Ability.Event.Knockback"), TEXT("Knockback Event"));
	
}

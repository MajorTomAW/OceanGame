// Copyright © 2024 MajorT. All rights reserved.

#include "OceanityGameTags.h"

// Damage
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Damage::Tag_Damage, "Damage", "Base Damage Tag");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Damage::Type::Tag_Type_Fire, "Damage.Type.Fire", "Fire Damage Type");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Damage::Event::Tag_Event_Hit, "Damage.Event.Hit", "Hit Event");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Damage::Event::Hit::Tag_Hit_Vital, "Damage.Event.Hit.Vital", "Vital Hit");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Damage::Event::Hit::Tag_Hit_Shield, "Damage.Event.Hit.Shield", "Shield Hit");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Damage::Event::Hit::Tag_Hit_DestroyShield, "Damage.Event.Hit.DestroyShield", "Shield Destroyed");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Damage::Event::Hit::Tag_Hit_Dead, "Damage.Event.Hit.Dead", "Entity Dead");

// Input
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_InputTag, "Input.InputTag", "Base Input Tag");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_LMB, "Input.InputTag.LMB", "Left Mouse Button");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_RMB, "Input.InputTag.RMB", "Right Mouse Button");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_Space, "Input.InputTag.Space", "Spacebar");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_1, "Input.InputTag.1", "Number 1 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_2, "Input.InputTag.2", "Number 2 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_3, "Input.InputTag.3", "Number 3 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_4, "Input.InputTag.4", "Number 4 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_5, "Input.InputTag.5", "Number 5 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_6, "Input.InputTag.6", "Number 6 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Input::Tag_7, "Input.InputTag.7", "Number 7 Key");

// Ability
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Tag_Ability, "Ability", "Base Ability Tag");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Descriptor::Tag_Descriptor_Melee, "Ability.Descriptor.Melee", "Melee Ability Descriptor");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Descriptor::Melee::Tag_Descriptor_Melee_Launch, "Ability.Descriptor.Melee.Launch", "Melee Launch Ability");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Descriptor::Tag_Descriptor_Ranged, "Ability.Descriptor.Ranged", "Ranged Ability Descriptor");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Descriptor::Ranged::Tag_Descriptor_Ranged_Shoot, "Ability.Descriptor.Ranged.Shoot", "Ranged Shoot Ability");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Descriptor::Tag_Descriptor_Boost, "Ability.Descriptor.Boost", "Boost Ability Descriptor");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Descriptor::Reload::Tag_Descriptor_Reload_ReloadAmmo, "Ability.Descriptor.Reload.ReloadAmmo", "Reload Ammo Ability");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Cooldown::Tag_Cooldown_Shoot, "Ability.Cooldown.Shoot", "Shoot Ability Cooldown");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Descriptor::Event::Tag_Descriptor_Event_HitReact, "Ability.Descriptor.Event.HitReact", "Hit React Ability Descriptor");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Ability::Cooldown::Tag_Cooldown_Boost, "Ability.Cooldown.Boost", "Boost Ability Cooldown");

// Attribute
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Tag_Attribute, "Attribute", "Base Attribute Tag");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Meta::Tag_Meta_IncomingCoins, "Attribute.Meta.IncomingCoins", "Incoming Coins Meta Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Meta::Tag_Meta_IncomingDamage, "Attribute.Meta.IncomingDamage", "Incoming Damage Meta Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Vital::Tag_Vital_MaxHealth, "Attribute.Vital.MaxHealth", "Max Health Vital Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Vital::Tag_Vital_Health, "Attribute.Vital.Health", "Health Vital Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Vital::Tag_Vital_Shield, "Attribute.Vital.Shield", "Shield Vital Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Vital::Tag_Vital_MaxShield, "Attribute.Vital.MaxShield", "Max Shield Vital Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Primary::Tag_Primary_Damage, "Attribute.Primary.Damage", "Damage Primary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Primary::Tag_Primary_Ammo, "Attribute.Primary.Ammo", "Ammo Primary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Primary::Tag_Primary_MaxAmmo, "Attribute.Primary.MaxAmmo", "Max Ammo Primary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Primary::Tag_Primary_ReloadSpeed, "Attribute.Primary.ReloadSpeed", "Reload Speed Primary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Primary::Tag_Primary_ShootCooldown, "Attribute.Primary.ShootCooldown", "Shoot Cooldown Primary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_MaxSpeed, "Attribute.Secondary.MaxSpeed", "Max Speed Secondary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_Acceleration, "Attribute.Secondary.Acceleration", "Acceleration Secondary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_TurnSpeed, "Attribute.Secondary.TurnSpeed", "Turn Speed Secondary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_Weight, "Attribute.Secondary.Weight", "Weight Secondary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Secondary::Tag_Secondary_BackwardsMultiplier, "Attribute.Secondary.BackwardsMultiplier", "Backwards Speed Multiplier Secondary Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Boost::Tag_Boost_BoostDuration, "Attribute.Boost.BoostDuration", "Boost Duration Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Boost::Tag_Boost_BoostCooldown, "Attribute.Boost.BoostCooldown", "Boost Cooldown Attribute");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Attribute::Boost::Tag_Boost_BoostSpeed, "Attribute.Boost.BoostSpeed", "Boost Speed Attribute");

// Gameplay
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Gameplay::Event::Hit::Tag_Hit_Success, "Gameplay.Event.Hit.Success", "Hit Success Event");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(OceanityGameplayTags::Gameplay::Event::Hit::Tag_Hit_Fail, "Gameplay.Event.Hit.Fail", "Hit Fail Event");
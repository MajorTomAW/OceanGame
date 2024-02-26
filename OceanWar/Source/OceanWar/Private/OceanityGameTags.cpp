// Copyright © 2024 MajorT. All rights reserved.

#include "OceanityGameTags.h"

namespace OceanityGameTags
{
	/** Damage */
	namespace Damage
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Damage, "Damage", "Base damage tag");

		namespace Type
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Fire, "Damage.Type.Fire", "Fire damage tag");	
		}

		namespace Event
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Hit, "Damage.Event.Hit", "Hit event tag");

			namespace Hit
			{
				UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Vital, "Damage.Event.Hit.Vital", "Hit and damaged the target's vitals");
				UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Shield, "Damage.Event.Hit.Shield", "Hit but target still has shield");
				UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_DestroyShield, "Damage.Event.Hit.DestroyShield", "Hit and destroyed the target's shield");
				UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Dead, "Damage.Event.Hit.Dead", "Hit and killed the target");
			}
		}
	}

	/** Input */
	namespace Input
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_InputTag, "Input.InputTag", "Base input tag");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_LMB, "Input.InputTag.LMB", "Left Mouse Button (SHOOT)");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_RMB, "Input.InputTag.RMB", "Right Mouse Button (AIM)");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Space, "Input.InputTag.Space", "Key Space (JUMP)");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_1, "Input.InputTag.1", "Key R (RELOAD)");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_2, "Input.InputTag.2", "Key Shift (BOOST)");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_3, "Input.InputTag.3", "Key (ABILITY E)");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_4, "Input.InputTag.4", "Key (ABILITY F)");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_5, "Input.InputTag.5", "Key (ABILITY Q)");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_6, "Input.InputTag.6", "Key (ABILITY R)");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_7, "Input.InputTag.7", "Key (ABILITY T)");
	}

	/** Ability */
	namespace Ability
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Ability, "Ability", "Base ability tag");

		namespace Descriptor
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Melee, "Ability.Descriptor.Melee", "Melee ability tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Launch, "Ability.Descriptor.Melee.Launch", "Launch melee ability tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Ranged, "Ability.Descriptor.Ranged", "Ranged ability tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Shoot, "Ability.Descriptor.Ranged.Shoot", "Shoot ranged ability tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Boost, "Ability.Descriptor.Boost", "Boost ability tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_ReloadAmmo, "Ability.Descriptor.Reload.Ammo", "Reload ammo ability tag");
		}

		namespace Cooldown
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Cooldown_Shoot, "Ability.Cooldown.Ranged.Shoot", "Shoot ability cooldown tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tag_Cooldown_Boost, "Ability.Cooldown.Boost", "Boost ability cooldown tag");
		}
	}
}
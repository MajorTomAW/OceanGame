// Copyright © 2024 MajorT. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


namespace OceanityGameplayTags
{
	/** Damage*/
	namespace Damage
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Damage)

		namespace Type
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Type_Fire)
		}

		namespace Event
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Event_Hit)

			namespace Hit
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Hit_Vital)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Hit_Shield)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Hit_DestroyShield)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Hit_Dead)
			}
		}
	}

	/** Input */
	namespace Input
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InputTag)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_LMB)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_RMB)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Space)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_1)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_2)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_3)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_4)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_5)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_6)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_7)
	}

	/** Ability */
	namespace Ability
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability)

		namespace Descriptor
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Descriptor_Melee)

			namespace Melee
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Descriptor_Melee_Launch)
			}

			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Descriptor_Ranged)

			namespace Ranged
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Descriptor_Ranged_Shoot)
			}


			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Descriptor_Boost)

			namespace Reload
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Descriptor_Reload_ReloadAmmo)
			}

			namespace Event
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Descriptor_Event_HitReact)				
			}
		}

		namespace Cooldown
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Cooldown_Shoot)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Cooldown_Boost)
		}
	}

	/** Attribute */
	namespace Attribute
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Attribute)

		namespace Meta
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Meta_IncomingCoins)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Meta_IncomingDamage)
		}

		namespace Vital
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Vital_MaxHealth)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Vital_Health)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Vital_Shield)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Vital_MaxShield)
		}

		namespace Primary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Primary_Damage)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Primary_Ammo)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Primary_MaxAmmo)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Primary_ReloadSpeed)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Primary_ShootCooldown)
		}

		namespace Secondary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Secondary_MaxSpeed)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Secondary_Acceleration)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Secondary_TurnSpeed)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Secondary_Weight)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Secondary_BackwardsMultiplier)
		}

		namespace Boost
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Boost_BoostDuration)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Boost_BoostCooldown)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Boost_BoostSpeed)
		}
	}

	/** Gameplay */
	namespace Gameplay
	{
		namespace Event
		{
			namespace Hit
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Hit_Success)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Hit_Fail)
			}
		}		
	}
}

// Copyright © 2024 MajorT. All rights reserved.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


namespace OceanityGameTags
{
	/** Damage*/
	namespace Damage
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Damage)

		namespace Type
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Fire)
		}

		namespace Event
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Hit)
			namespace Hit
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Vital)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Shield)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_DestroyShield)
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Dead)
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
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Melee)
			namespace Melee
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Launch)				
			}

			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ranged)
			namespace Ranged
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Shoot)
			}


			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Boost)
			namespace Reload
			{
				UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_ReloadAmmo)
			}
		}

		namespace Cooldown
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Cooldown_Shoot)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Cooldown_Boost)
		}
	}
}

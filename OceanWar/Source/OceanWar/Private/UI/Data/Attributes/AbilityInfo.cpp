// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Data/Attributes/AbilityInfo.h"

#include "Log/OceanityLogChannels.h"

FOceanityAbilityInfo UAbilityInfo::FindAbilityInfoByTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FOceanityAbilityInfo& AbilityInfo : AbilityInfos)
	{
		if (AbilityInfo.AbilityTag.MatchesTagExact(Tag))
		{
			return AbilityInfo;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogOceanityUI, Warning, TEXT("AbilityInfo with tag %s not found"), *Tag.ToString());
	}

	return FOceanityAbilityInfo();
}

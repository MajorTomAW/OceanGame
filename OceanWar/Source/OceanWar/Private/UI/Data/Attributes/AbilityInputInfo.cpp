// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Data/Attributes/AbilityInputInfo.h"

FOceanityAbilityInputInfo UAbilityInputInfo::FindAbilityInputInfoByTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	for (const FOceanityAbilityInputInfo& Info : InputInfos)
	{
		if (Info.InputTag.MatchesTagExact(Tag))
		{
			return Info;
		}
	}

	return FOceanityAbilityInputInfo();
}

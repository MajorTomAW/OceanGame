// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Data/Damage/DamageInfo.h"


void UDamageInfo::GetUIDamageInfoFromTag(UDamageInfo* DataAsset, const FGameplayTag& Tag, bool& bFound, FUIDamageInfo& OutInfo)
{
	for (const FUIDamageInfo& Info : DataAsset->DamageInfo)
	{
		if (Info.DamageTag.MatchesTag(Tag))
		{
			OutInfo = Info;
			bFound = true;
			return;
		}
	}
	bFound = false;
}

// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/Data/Cashout/CoinEarnInfo.h"

int32 UCoinEarnInfo::GetCoinsEarned(const FGameplayTagContainer& DamageTags) const
{
	int32 TotalCoins = 0;
	for (const FCoinEarnInfoStruct& CoinEarnInfo : CoinEarnInfos)
	{
		if (DamageTags.HasTagExact(CoinEarnInfo.DamageTag))
		{
			TotalCoins += CoinEarnInfo.CoinsEarned;
		}
	}
	return TotalCoins;
}

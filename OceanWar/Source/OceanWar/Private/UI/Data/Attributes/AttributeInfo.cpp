// Copyright © 2024 MajorT. All rights reserved.


#include "UI/Data/Attributes/AttributeInfo.h"

#include "Log/OceanityLogChannels.h"

FOceanityAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& InTag, bool bLogNotFound) const
{
	for (const FOceanityAttributeInfo& AttributeInfo : AttributeInfos)
	{
		if (AttributeInfo.AttributeTag.MatchesTagExact(InTag))
		{
			return AttributeInfo;
		}
	}
	if (bLogNotFound) UE_LOG(LogOceanityGAS, Warning, TEXT("AttributeInfo not found for tag: %s"), *InTag.ToString());
	return FOceanityAttributeInfo();
}

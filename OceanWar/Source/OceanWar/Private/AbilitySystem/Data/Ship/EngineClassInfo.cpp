// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/Data/Ship/EngineClassInfo.h"

FShipClassDefaultInfo UEngineClassInfo::GetEngineClassDefaults(EEngineClassType EngineClassType)
{
	return EngineClassDefaults.FindChecked(EngineClassType);
}

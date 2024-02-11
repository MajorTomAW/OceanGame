// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/Data/Ship/HullClassInfo.h"

FShipClassDefaultInfo UHullClassInfo::GetHullClassDefaults(EHullClassType HullClassType)
{
	return HullClassDefaults.FindChecked(HullClassType);
}

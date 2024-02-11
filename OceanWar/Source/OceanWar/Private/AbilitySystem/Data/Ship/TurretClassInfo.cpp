// Copyright © 2024 MajorT. All rights reserved.


#include "AbilitySystem/Data/Ship/TurretClassInfo.h"

FShipClassDefaultInfo UTurretClassInfo::GetTurretClassDefaults(ETurretClassType TurretClassType)
{
	return TurretClassDefaults.FindChecked(TurretClassType);
}

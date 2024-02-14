// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OCEANWAR_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetCombatSocketLocation() const {return FVector::ZeroVector; }
};

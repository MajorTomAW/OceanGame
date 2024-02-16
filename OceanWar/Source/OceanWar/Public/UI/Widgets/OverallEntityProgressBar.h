// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "OverallProgressBar.h"
#include "OverallEntityProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class OCEANWAR_API UOverallEntityProgressBar : public UOverallProgressBar
{
	GENERATED_BODY()

protected:
	virtual void BindToRespondingAttributes() override;
};

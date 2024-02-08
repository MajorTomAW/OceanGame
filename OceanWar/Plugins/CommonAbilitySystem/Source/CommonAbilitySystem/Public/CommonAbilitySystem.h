// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(CommonAbilityLog, Log, All);

#define Tag_Enemy FName(TEXT("Enemy"))
#define Tag_Player FName(TEXT("Player"))

class FCommonAbilitySystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

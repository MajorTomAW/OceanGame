// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "GameFramework/PlayerState.h"

struct FOnlineSubsystemBPCallHelperCommon
{
public:
	FOnlineSubsystemBPCallHelperCommon(const TCHAR* CallFunctionContext, UWorld* World, FName SystemName = NAME_None)
		: OnlineSub(Online::GetSubsystem(World, SystemName))
		, FunctionContext(CallFunctionContext)
	{
		if (OnlineSub == nullptr)
		{
			FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Invalid or uninitialized OnlineSubsystem"), FunctionContext), ELogVerbosity::Warning);
		}
	}

	void QueryIDFromPlayerController(APlayerController* PlayerController)
	{
		UserID.Reset();
		//return const_cast<FUniqueNetId*>(UniqueNetIdPtr);
		if (APlayerState* PlayerState = (PlayerController != NULL) ? PlayerController->PlayerState : NULL)
		{
			UserID = PlayerState->GetUniqueId().GetUniqueNetId();
			if (!UserID.IsValid())
			{
				FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Cannot map local player to unique net ID"), FunctionContext), ELogVerbosity::Warning);
			}
		}
		else
		{
			FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Invalid player state"), FunctionContext), ELogVerbosity::Warning);
		}
	}


	bool IsValid() const
	{
		return UserID.IsValid() && (OnlineSub != nullptr);
	}

public:
	//TSharedPtr<const FUniqueNetId>& GetUniqueNetId()
	TSharedPtr</*class*/ const FUniqueNetId> UserID;
	IOnlineSubsystem* const OnlineSub;
	const TCHAR* FunctionContext;
};

class FCommonSubsystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

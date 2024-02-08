// Copyright © 2023 MajorT. All rights reserved.


#include "CommonFindSession.h"

#include "CommonSubsystem.h"
#include "Data/CommonDataDefinitions.h"
#include "Online/OnlineSessionNames.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/OnlineSessionInterface.h"

UCommonFindSession::UCommonFindSession(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Delegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnCompleted))
	, bUseLan(false)
{
	bRunSecondSearch = false;
	bIsOnSecondSearch = false;
}

UCommonFindSession* UCommonFindSession::FindCommonSessions(UObject* WorldContextObject,
	APlayerController* PlayerController, int32 MaxResults, bool bUseLan, bool bSearchLobbies)
{
	UCommonFindSession* MyObj = NewObject<UCommonFindSession>();
	MyObj->PlayerControllerWeakPtr = PlayerController;
	MyObj->MaxResults = MaxResults;
	MyObj->bUseLan = bUseLan;
	MyObj->bSearchLobbies = bSearchLobbies;
	MyObj->WorldContextObject = WorldContextObject;
	return MyObj;
}

void UCommonFindSession::Activate()
{
	FOnlineSubsystemBPCallHelperCommon Helper(TEXT("FindSessions"), GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull));
	Helper.QueryIDFromPlayerController(PlayerControllerWeakPtr.Get());

	if (Helper.IsValid())
	{
		auto Sessions = Helper.OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			DelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(Delegate);
			SearchObject = MakeShareable(new FOnlineSessionSearch);
			SearchObject->MaxSearchResults = MaxResults;
			SearchObject->bIsLanQuery = bUseLan;
			SearchObject->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
			if (bSearchLobbies) // If we want to search for lobbies
			{
				SearchObject->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
			}
			Sessions->FindSessions(*Helper.UserID, SearchObject.ToSharedRef());

			// OnQueryCompleted will get called, nothing more to do now
			return;
		}
		UE_LOG(CommonSessionsLog, Warning, TEXT("FindSessions failed. Sessions not supported by Online Subsystem."));
	}

	const TArray<FBlueprintSessionResult> Results;
	OnFailure.Broadcast(Results);
}

void UCommonFindSession::OnCompleted(bool bSuccess)
{
	FOnlineSubsystemBPCallHelperCommon Helper(TEXT("FindSessionsCallback"), GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull));
	Helper.QueryIDFromPlayerController(PlayerControllerWeakPtr.Get());

	if (Helper.IsValid())
	{
		auto Sessions = Helper.OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnFindSessionsCompleteDelegate_Handle(DelegateHandle);
		}
	}

	TArray<FBlueprintSessionResult> Results;

	if (bSuccess && SearchObject.IsValid())
	{
		for (auto& Result : SearchObject->SearchResults)
		{
			FBlueprintSessionResult BPResult;
			BPResult.OnlineResult = Result;
			Results.Add(BPResult);
		}

		OnSuccess.Broadcast(Results);
	}
	else
	{
		UE_LOG(CommonSessionsLog, Warning, TEXT("FindSessions failed."));
		OnFailure.Broadcast(Results);
	}
}

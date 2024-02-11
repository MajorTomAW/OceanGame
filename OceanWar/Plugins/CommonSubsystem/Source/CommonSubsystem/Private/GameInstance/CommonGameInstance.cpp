// Copyright © 2024 MajorT. All rights reserved.


#include "GameInstance/CommonGameInstance.h"

#include "FindSessionsCallbackProxy.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystemUtils.h"
#include "Data/CommonDataDefinitions.h"
#include "GameFramework/PlayerController.h"

UCommonGameInstance::UCommonGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
, bCallFriendInterfaceEventsOnPlayerControllers(true)
, bCallIdentityInterfaceEventsOnPlayerControllers(true)
, bCallVoiceInterfaceEventsOnPlayerControllers(true)
, bEnableTalkingStatusDelegate(true)
, SessionInviteReceivedDelegate(FOnSessionInviteReceivedDelegate::CreateUObject(this, &UCommonGameInstance::OnSessionInviteReceivedMaster))
, SessionInviteAcceptedDelegate(FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &UCommonGameInstance::OnSessionInviteAcceptedMaster))
, PlayerTalkingStateChangedDelegate(FOnPlayerTalkingStateChangedDelegate::CreateUObject(this, &UCommonGameInstance::OnPlayerTalkingStateChangedMaster))
, PlayerLoginStatusChangedDelegate(FOnLoginStatusChangedDelegate::CreateUObject(this, &UCommonGameInstance::OnPlayerLoginStatusChangedMaster))
, PlayerLoginChangedDelegate(FOnLoginChangedDelegate::CreateUObject(this, &UCommonGameInstance::OnPlayerLoginChangedMaster))
{
}

void UCommonGameInstance::Shutdown()
{
	IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	
	if (!SessionInterface.IsValid())
	{
		//UE_LOG(AdvancedFriendsInterfaceLog, Warning, TEXT("UAdvancedFriendsGameInstance Failed to get session system!"));
		//return;
	}
	else
	{
		// Clear all of the delegate handles here
		SessionInterface->ClearOnSessionUserInviteAcceptedDelegate_Handle(SessionInviteAcceptedDelegateHandle);
		SessionInterface->ClearOnSessionInviteReceivedDelegate_Handle(SessionInviteReceivedDelegateHandle);
	}


	if (bEnableTalkingStatusDelegate)
	{
		IOnlineVoicePtr VoiceInterface = Online::GetVoiceInterface(GetWorld());

		if (VoiceInterface.IsValid())
		{
			VoiceInterface->ClearOnPlayerTalkingStateChangedDelegate_Handle(PlayerTalkingStateChangedDelegateHandle);
		}
		else
		{

			//UE_LOG(AdvancedFriendsInterfaceLog, Warning, TEXT("UAdvancedFriendsInstance Failed to get voice interface!"));
		}
	}

	IOnlineIdentityPtr IdentityInterface = Online::GetIdentityInterface(GetWorld());

	if (IdentityInterface.IsValid())
	{
		IdentityInterface->ClearOnLoginChangedDelegate_Handle(PlayerLoginChangedDelegateHandle);
		

		// I am just defaulting to player 1
		IdentityInterface->ClearOnLoginStatusChangedDelegate_Handle(0, PlayerLoginStatusChangedDelegateHandle);
	}


	Super::Shutdown();
}

void UCommonGameInstance::Init()
{
	IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());//OnlineSub->GetSessionInterface();

	if (SessionInterface.IsValid())
	{
		// Currently doesn't store a handle or assign a delegate to any local player beyond the first.....should handle?
		// Thought about directly handling it but friends for multiple players probably isn't required
		// Iterating through the local player TArray only works if it has had players assigned to it, most of the online interfaces don't support
		// Multiple logins either (IE: Steam)
		SessionInviteAcceptedDelegateHandle = SessionInterface->AddOnSessionUserInviteAcceptedDelegate_Handle(SessionInviteAcceptedDelegate);

		SessionInviteReceivedDelegateHandle = SessionInterface->AddOnSessionInviteReceivedDelegate_Handle(SessionInviteReceivedDelegate);
	}
	else
	{
		//UE_LOG(AdvancedFriendsInterfaceLog, Warning, TEXT("UAdvancedFriendsInstance Failed to get session interface!"));
		//return;
	}

	// Beginning work on the voice interface
	if (bEnableTalkingStatusDelegate)
	{
		IOnlineVoicePtr VoiceInterface = Online::GetVoiceInterface(GetWorld());

		if (VoiceInterface.IsValid())
		{
			PlayerTalkingStateChangedDelegateHandle = VoiceInterface->AddOnPlayerTalkingStateChangedDelegate_Handle(PlayerTalkingStateChangedDelegate);
		}
		else
		{

			//UE_LOG(AdvancedFriendsInterfaceLog, Warning, TEXT("UAdvancedFriendsInstance Failed to get voice interface!"));
		}
	}

	IOnlineIdentityPtr IdentityInterface = Online::GetIdentityInterface(GetWorld());

	if (IdentityInterface.IsValid())
	{
		PlayerLoginChangedDelegateHandle = IdentityInterface->AddOnLoginChangedDelegate_Handle(PlayerLoginChangedDelegate);

		// Just defaulting to player 1
		PlayerLoginStatusChangedDelegateHandle = IdentityInterface->AddOnLoginStatusChangedDelegate_Handle(0, PlayerLoginStatusChangedDelegate);
	}
	else
	{
		//UE_LOG(AdvancedFriendsInterfaceLog, Warning, TEXT("UAdvancedFriendsInstance Failed to get identity interface!"));
	}


	Super::Init();
}

void UCommonGameInstance::OnSessionInviteReceivedMaster(const FUniqueNetId& PersonInvited,
	const FUniqueNetId& PersonInviting, const FString& AppId, const FOnlineSessionSearchResult& SessionToJoin)
{
	if (SessionToJoin.IsValid())
	{
		FBlueprintSessionResult BluePrintResult;
		BluePrintResult.OnlineResult = SessionToJoin;

		FBPUniqueNetId PInvited;
		PInvited.SetUniqueNetId(&PersonInvited);

		FBPUniqueNetId PInviting;
		PInviting.SetUniqueNetId(&PersonInviting);


		TArray<APlayerController*> PlayerList;
		GEngine->GetAllLocalPlayerControllers(PlayerList);

		APlayerController* Player = NULL;

		int32 LocalPlayer = 0;
		for (int i = 0; i < PlayerList.Num(); i++)
		{
			if (*PlayerList[i]->PlayerState->GetUniqueId().GetUniqueNetId() == PersonInvited)
			{
				LocalPlayer = i;
				Player = PlayerList[i];
				break;
			}
		}

		OnSessionInviteReceived(LocalPlayer, PInviting, AppId, BluePrintResult);

		//IAdvancedFriendsInterface* TheInterface = NULL;

		if (Player != NULL)
		{
			//Run the Event specific to the actor, if the actor has the interface, otherwise ignore
			//if (Player->GetClass()->ImplementsInterface(UAdvancedFriendsInterface::StaticClass()))
			//{
			//	IAdvancedFriendsInterface::Execute_OnSessionInviteReceived(Player, PInviting, BluePrintResult);
			//}
		}
		else
		{
			//UE_LOG(AdvancedFriendsInterfaceLog, Warning, TEXT("UAdvancedFriendsInstance Failed to get a controller with the specified index in OnSessionInviteReceived!"));
		}
	}
	else
	{
		//UE_LOG(AdvancedFriendsInterfaceLog, Warning, TEXT("UAdvancedFriendsInstance Return a bad search result in OnSessionInviteReceived!"));
	}
}

void UCommonGameInstance::OnSessionInviteAcceptedMaster(const bool bWasSuccessful, int32 LocalPlayer,
	TSharedPtr<const FUniqueNetId> PersonInviting, const FOnlineSessionSearchResult& SessionToJoin)
{
	if (bWasSuccessful)
	{
		if (SessionToJoin.IsValid())
		{

			FBlueprintSessionResult BluePrintResult;
			BluePrintResult.OnlineResult = SessionToJoin;

			FBPUniqueNetId PInvited;
			PInvited.SetUniqueNetId(PersonInviting);

			OnSessionInviteAccepted(LocalPlayer,PInvited, BluePrintResult);

			APlayerController* Player = UGameplayStatics::GetPlayerController(GetWorld(), LocalPlayer);

			//IAdvancedFriendsInterface* TheInterface = NULL;

			if (Player != NULL)
			{
				//Run the Event specific to the actor, if the actor has the interface, otherwise ignore
				//if (Player->GetClass()->ImplementsInterface(UAdvancedFriendsInterface::StaticClass()))
				//{
				//	IAdvancedFriendsInterface::Execute_OnSessionInviteAccepted(Player,PInvited, BluePrintResult);
				//}
			}
			else
			{ 
				//UE_LOG(AdvancedFriendsInterfaceLog, Warning, TEXT("UAdvancedFriendsInstance Failed to get a controller with the specified index in OnSessionInviteAccepted!"));
			}
		}
		else
		{
			//UE_LOG(AdvancedFriendsInterfaceLog, Warning, TEXT("UAdvancedFriendsInstance Return a bad search result in OnSessionInviteAccepted!"));
		}
	}
}

void UCommonGameInstance::OnPlayerTalkingStateChangedMaster(TSharedRef<const FUniqueNetId> PlayerId, bool bIsTalking)
{
}

void UCommonGameInstance::OnPlayerLoginChangedMaster(int32 PlayerNum)
{
}

void UCommonGameInstance::OnPlayerLoginStatusChangedMaster(int32 PlayerNum, ELoginStatus::Type PreviousStatus,
	ELoginStatus::Type NewStatus, const FUniqueNetId& NewPlayerUniqueNetID)
{
}

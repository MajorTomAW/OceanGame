// Copyright © 2023 MajorT. All rights reserved.


#include "BlueprintLibraries/CommonFriendsLibrary.h"
#include "Interfaces/OnlinePresenceInterface.h"

void UCommonFriendsLibrary::SendSessionInviteToFriend(APlayerController* PlayerController,
	const FBPUniqueNetId& FriendUniqueNetId, TEnumAsByte<EBlueprintResultSwitch>& Result)
{
	if (!PlayerController)
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("SendSessionInviteToFriend Had a bad Player Controller!"));
		Result = OnFailure;
		return;
	}
	if (!FriendUniqueNetId.IsValid())
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("SendSessionInviteToFriend Had a bad UniqueNetId!"));
		Result = OnFailure;
		return;
	}

	const IOnlineSessionPtr SessionPtr = Online::GetSessionInterface(GEngine->GetWorldFromContextObject(PlayerController, EGetWorldErrorMode::LogAndReturnNull));

	if (!SessionPtr.IsValid())
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("SendSessionInviteToFriend Failed to get session interface!"));
		Result = OnFailure;
		return;
	}

	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);

	if (!LocalPlayer)
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("SendSessionInviteToFriend failed to get LocalPlayer!"));
		Result = OnFailure;
		return;
	}

	if (SessionPtr->SendSessionInviteToFriend(LocalPlayer->GetControllerId(), NAME_GameSession, *FriendUniqueNetId.GetUniqueNetId()))
	{
		Result = OnSuccess;
		return;
	}

	Result = OnFailure;
}

void UCommonFriendsLibrary::GetStoredFriendsList(APlayerController* PlayerController,
	TArray<FBPFriendInfo>& FriendsList)
{
	if (!PlayerController)
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("GetStoredFriendsList Had a bad Player Controller!"));
		return;
	}

	const IOnlineFriendsPtr FriendsPtr = Online::GetFriendsInterface(GEngine->GetWorldFromContextObject(PlayerController, EGetWorldErrorMode::LogAndReturnNull));

	if (!FriendsPtr.IsValid())
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("GetStoredFriendsList Failed to get friends interface!"));
		return;
	}

	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);

	if (!IsValid(LocalPlayer))
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("GetStoredFriendsList failed to get LocalPlayer!"));
		return;
	}

	TArray<TSharedRef<FOnlineFriend>> FriendList;
	FriendsPtr->GetFriendsList(LocalPlayer->GetControllerId(), EFriendsLists::ToString(EFriendsLists::Default), FriendList);

	for (int32 i = 0; i < FriendList.Num(); i++)
	{
		TSharedRef<FOnlineFriend> Friend = FriendList[i];
		FBPFriendInfo FriendInfo;
		FOnlineUserPresence Presence = Friend->GetPresence();

		UE_LOG(CommonFriendsLog, Warning, TEXT("GetStoredFriendsList: Friend: %s"), *Friend->GetDisplayName());
		FriendInfo.OnlineState = static_cast<EBPOnlinePresenceState>(static_cast<int32>(Presence.Status.State));
		FriendInfo.DisplayName = Friend->GetDisplayName();
		FriendInfo.RealName = Friend->GetRealName();
		FriendInfo.UniqueNetId.SetUniqueNetId(Friend->GetUserId());
		FriendInfo.bIsPlayingSameGame = Presence.bIsPlayingThisGame;
		
		FriendInfo.PresenceInfo.bIsOnline = Presence.bIsOnline;
		FriendInfo.PresenceInfo.bIsPlaying = Presence.bIsPlaying;
		FriendInfo.PresenceInfo.bIsPlayingThisGame = Presence.bIsPlayingThisGame;
		FriendInfo.PresenceInfo.bIsJoinable = Presence.bIsJoinable;
		FriendInfo.PresenceInfo.bHasVoiceSupport = Presence.bHasVoiceSupport;
		FriendInfo.PresenceInfo.PresenceState = static_cast<EBPOnlinePresenceState>(static_cast<int32>(Presence.Status.State));
		FriendInfo.PresenceInfo.StatusString = Presence.Status.StatusStr;

		FriendsList.Add(FriendInfo);
	}
}

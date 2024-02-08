// Copyright © 2023 MajorT. All rights reserved.


#include "CommonGetFriends.h"

#include "Data/CommonDataDefinitions.h"
#include "Interfaces/OnlinePresenceInterface.h"

UCommonGetFriends::UCommonGetFriends(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, FriendsListCompleteDelegate(FOnReadFriendsListComplete::CreateUObject(this, &ThisClass::OnFindFriendsCompleted))
{
}

UCommonGetFriends* UCommonGetFriends::GetFriendsList(UObject* WorldContextObject, APlayerController* PlayerController)
{
	UCommonGetFriends* MyObj = NewObject<UCommonGetFriends>();
	MyObj->PlayerControllerWeakPtr = PlayerController;
	MyObj->WorldContextObject = WorldContextObject;
	return MyObj;
}

void UCommonGetFriends::Activate()
{
	if (!PlayerControllerWeakPtr.IsValid())
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("GetFriends Failed received a bad player controller!"));
		OnFailure.Broadcast(TArray<FBPFriendInfo>());
		return;
	}

	const IOnlineFriendsPtr FriendsPtr = Online::GetFriendsInterface(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull));

	if (FriendsPtr.IsValid())
	{
		ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerControllerWeakPtr->Player);
		FriendsPtr->ReadFriendsList(LocalPlayer->GetControllerId(), EFriendsLists::ToString(EFriendsLists::Default), FriendsListCompleteDelegate);
		return;
	}

	OnFailure.Broadcast(TArray<FBPFriendInfo>());
}

void UCommonGetFriends::OnFindFriendsCompleted(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName,
	const FString& ErrorString)
{
	if (bWasSuccessful)
	{
		const IOnlineFriendsPtr FriendsPtr = Online::GetFriendsInterface(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull));
		if (FriendsPtr.IsValid())
		{
			TArray<FBPFriendInfo> FoundFriends;
			TArray<TSharedRef<FOnlineFriend>> FriendList;
			FriendsPtr->GetFriendsList(LocalUserNum, ListName, FriendList);

			for (const TSharedRef<FOnlineFriend>& Friend : FriendList)
			{
				FBPFriendInfo FriendInfo;
				FOnlineUserPresence Presence = Friend->GetPresence();

				FriendInfo.OnlineState = static_cast<EBPOnlinePresenceState>(static_cast<int32>(Presence.Status.State));
				FriendInfo.DisplayName = Friend->GetDisplayName();
				FriendInfo.RealName = Friend->GetRealName();
				FriendInfo.UniqueNetId.SetUniqueNetId(Friend->GetUserId());

				FriendInfo.PresenceInfo.bIsOnline = Presence.bIsOnline;
				FriendInfo.PresenceInfo.bHasVoiceSupport = Presence.bHasVoiceSupport;
				FriendInfo.PresenceInfo.bIsPlaying = Presence.bIsPlaying;
				FriendInfo.PresenceInfo.PresenceState = static_cast<EBPOnlinePresenceState>(static_cast<int32>(Presence.Status.State));
				FriendInfo.PresenceInfo.StatusString = Presence.Status.StatusStr;
				FriendInfo.PresenceInfo.bIsJoinable = Presence.bIsJoinable;
				FriendInfo.PresenceInfo.bIsPlayingThisGame = Presence.bIsPlayingThisGame;

				FoundFriends.Add(FriendInfo);
			}

			OnSuccess.Broadcast(FoundFriends);
		}
	}
	else
	{
		OnFailure.Broadcast(TArray<FBPFriendInfo>());
	}
}

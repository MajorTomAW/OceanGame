// Copyright © 2023 MajorT. All rights reserved.


#include "SendFriendInviteCallback.h"

USendFriendInviteCallback::USendFriendInviteCallback(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, OnSendInviteCompleteDelegate(FOnSendInviteComplete::CreateUObject(this, &ThisClass::OnSendFriendInviteComplete))
{
}

USendFriendInviteCallback* USendFriendInviteCallback::SendFriendInvite(UObject* WorldContextObject,
	APlayerController* PlayerController, const FBPUniqueNetId& UniqueNetIDInvited)
{
	USendFriendInviteCallback* MyObj = NewObject<USendFriendInviteCallback>();
	MyObj->PlayerControllerWeakPtr = PlayerController;
	MyObj->UniqueNetIdToInvite = UniqueNetIDInvited;
	MyObj->WorldContextObject = WorldContextObject;
	return MyObj;
}

void USendFriendInviteCallback::Activate()
{
	if (!UniqueNetIdToInvite.IsValid())
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("SendFriendInvite Failed received a bad UniqueNetId!"));
		OnFailure.Broadcast(TEXT("SendFriendInvite Failed received a bad UniqueNetId!"));
		return;
	}
	if (!PlayerControllerWeakPtr.IsValid())
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("SendFriendInvite Failed received a bad playercontroller!"));
		OnFailure.Broadcast(TEXT("SendFriendInvite Failed received a bad playercontroller!"));
		return;
	}

	IOnlineFriendsPtr FriendsPtr = Online::GetFriendsInterface(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull));
	if (FriendsPtr.IsValid())
	{
		ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerControllerWeakPtr->Player);
		if (!LocalPlayer)
		{
			UE_LOG(CommonFriendsLog, Warning, TEXT("SendFriendInvite Failed couldn't cast to ULocalPlayer!"));
			OnFailure.Broadcast(TEXT("SendFriendInvite Failed couldn't cast to ULocalPlayer!"));
			return;
		}

		FriendsPtr->SendInvite(LocalPlayer->GetControllerId(), *UniqueNetIdToInvite.GetUniqueNetId(), EFriendsLists::ToString(EFriendsLists::Default), OnSendInviteCompleteDelegate);
		return;
	}
	OnFailure.Broadcast(TEXT("SendFriendInvite Failed couldn't get the friends interface!"));
}

void USendFriendInviteCallback::OnSendFriendInviteComplete(int32 LocalPlayerNum, bool bWasSuccessful,
	const FUniqueNetId& InvitedPlayer, const FString& ListName, const FString& ErrorString)
{
	if (bWasSuccessful)
	{
		OnSuccess.Broadcast(TEXT("SendFriendInvite was successful!"));
	}
	else
	{
		UE_LOG(CommonFriendsLog, Warning, TEXT("SendFriendInvite Failed with error: %s"), *ErrorString);
		OnFailure.Broadcast(ErrorString);
	}
}

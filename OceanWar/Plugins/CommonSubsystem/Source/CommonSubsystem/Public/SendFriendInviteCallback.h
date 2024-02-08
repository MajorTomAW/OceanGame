// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/CommonDataDefinitions.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "SendFriendInviteCallback.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlueprintSendFriendInviteDelegate, const FString&, Log);

/**
 * 
 */
UCLASS()
class COMMONSUBSYSTEM_API USendFriendInviteCallback : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FBlueprintSendFriendInviteDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FBlueprintSendFriendInviteDelegate OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Online|CommonSubsystem|Friends")
	static USendFriendInviteCallback* SendFriendInvite(UObject* WorldContextObject, APlayerController *PlayerController, const FBPUniqueNetId &UniqueNetIDInvited);

	virtual void Activate() override;

private:
	void OnSendFriendInviteComplete(int32 LocalPlayerNum, bool bWasSuccessful, const FUniqueNetId &InvitedPlayer, const FString &ListName, const FString &ErrorString);

	TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;
	FBPUniqueNetId UniqueNetIdToInvite;
	FOnSendInviteComplete OnSendInviteCompleteDelegate;
	UObject* WorldContextObject;
};

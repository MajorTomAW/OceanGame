// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "CommonGetFriends.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlueprintGetFriendsListDelegate, const TArray<FBPFriendInfo>&, Results);
/**
 * Retrieves the players list of friends from the OnlineSubsystem and returns it
 */
UCLASS()
class COMMONSUBSYSTEM_API UCommonGetFriends : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FBlueprintGetFriendsListDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FBlueprintGetFriendsListDelegate OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Online|CommonSubsystem|Friends")
	static UCommonGetFriends* GetFriendsList(UObject* WorldContextObject, class APlayerController* PlayerController);

	virtual void Activate() override;

private:
	void OnFindFriendsCompleted(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorString);

	TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;
	FOnReadFriendsListComplete FriendsListCompleteDelegate;
	UObject* WorldContextObject;
};

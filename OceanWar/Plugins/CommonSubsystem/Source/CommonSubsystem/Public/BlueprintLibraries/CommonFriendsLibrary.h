// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/CommonDataDefinitions.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonFriendsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class COMMONSUBSYSTEM_API UCommonFriendsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Online|CommonSubsystem|Friends", meta = (ExpandEnumAsExecs = "Result"))
	static void SendSessionInviteToFriend(APlayerController* PlayerController, const FBPUniqueNetId& FriendUniqueNetId, TEnumAsByte<EBlueprintResultSwitch>& Result);

	UFUNCTION(BlueprintCallable, Category = "Online|CommonSubsystem|Friends")
	static void GetStoredFriendsList(APlayerController* PlayerController, TArray<FBPFriendInfo>& FriendsList);
};

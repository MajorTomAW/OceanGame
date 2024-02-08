// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "FindSessionsCallbackProxy.h"
#include "CommonFindSession.generated.h"

FORCEINLINE bool operator==(const FBlueprintSessionResult& A, const FBlueprintSessionResult& B)
{
	return (A.OnlineResult.IsValid() == B.OnlineResult.IsValid() && (A.OnlineResult.GetSessionIdStr() == B.OnlineResult.GetSessionIdStr()));
}
/**
 * 
 */
UCLASS()
class COMMONSUBSYSTEM_API UCommonFindSession : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FBlueprintFindSessionsResultDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FBlueprintFindSessionsResultDelegate OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Online|CommonSubsystem")
	static UCommonFindSession* FindCommonSessions(UObject* WorldContextObject, class APlayerController* PlayerController, int32 MaxResults, bool bUseLan, bool bSearchLobbies = true);

	// static bool CompareVariants(const FVariantData& A, const FVariantData& B, EOnlineComparisonOpRedux Comparator);
	virtual void Activate() override;

private:
	void OnCompleted(bool bSuccess);
	bool bRunSecondSearch;
	bool bIsOnSecondSearch;

	TArray<FBlueprintSessionResult> SessionSearchResults;
	TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;

	FOnFindSessionsCompleteDelegate Delegate;
	FDelegateHandle DelegateHandle;
	TSharedPtr<FOnlineSessionSearch> SearchObject;
	TSharedPtr<FOnlineSessionSearch> SearchObjectDedicated;
	UObject* WorldContextObject;
	int MaxResults;
	bool bUseLan;
	bool bSearchLobbies;
};

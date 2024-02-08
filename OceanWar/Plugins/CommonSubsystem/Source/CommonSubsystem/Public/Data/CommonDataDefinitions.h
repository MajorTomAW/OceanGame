#pragma once
#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineDelegateMacros.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemUtilsModule.h"
#include "GameFramework/PlayerController.h"
#include "Modules/ModuleManager.h"
#include "CommonDataDefinitions.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CommonFriendsLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(CommonSessionsLog, Log, All);



UENUM(BlueprintType)
enum class EBPOnlinePresenceState : uint8
{
	Online,
	Offline,
	Away,
	ExtendedAway,
	DoNotDisturb,
	Chat
};

UENUM(BlueprintType)
enum EBlueprintResultSwitch
{
	OnSuccess,
	OnFailure
};

USTRUCT(BlueprintType)
struct FBPUniqueNetId
{
	GENERATED_USTRUCT_BODY()

private:
	bool bUseDirectPointer;
	
public:
	TSharedPtr<const FUniqueNetId> UniqueNetId;
	const FUniqueNetId* UniqueNetIdPtr;

	FBPUniqueNetId()
	{
		bUseDirectPointer = false;
		UniqueNetIdPtr = nullptr;
	}

	void SetUniqueNetId(const TSharedPtr<const FUniqueNetId> &ID)
	{
		bUseDirectPointer = false;
		UniqueNetIdPtr = nullptr;
		UniqueNetId = ID;
	}

	void SetUniqueNetId(const FUniqueNetId* ID)
	{
		bUseDirectPointer = true;
		UniqueNetIdPtr = ID;
	}

	bool IsValid() const
	{
		if (bUseDirectPointer && UniqueNetIdPtr != nullptr && UniqueNetIdPtr->IsValid())
		{
			return true;
		}
		if (UniqueNetId.IsValid())
		{
			return true;
		}
		return false;
	}

	const FUniqueNetId* GetUniqueNetId() const
	{
		if (bUseDirectPointer && UniqueNetIdPtr != nullptr)
		{
			return UniqueNetIdPtr;
		}
		if (UniqueNetId.IsValid())
		{
			return UniqueNetId.Get();
		}
		return nullptr;
	}

	FORCEINLINE bool operator==(const FBPUniqueNetId& A) const
	{
		return (IsValid() && A.IsValid() && (*GetUniqueNetId() == *A.GetUniqueNetId()));
	}

	FORCEINLINE bool operator!=(const FBPUniqueNetId& A) const
	{
		return !(IsValid() && A.IsValid() && (*GetUniqueNetId() == *A.GetUniqueNetId()));
	}
};

USTRUCT(BlueprintType)
struct FBPFriendPresenceInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	bool bIsOnline = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	bool bIsPlaying = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	bool bIsPlayingThisGame = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	bool bIsJoinable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	bool bHasVoiceSupport = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	EBPOnlinePresenceState PresenceState = EBPOnlinePresenceState::Offline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	FString StatusString;

	FBPFriendPresenceInfo()
	{
		bIsOnline = false;
		bIsPlaying = false;
		bIsPlayingThisGame = false;
		bIsJoinable = false;
		bHasVoiceSupport = false;
		PresenceState = EBPOnlinePresenceState::Offline;
	}
};

USTRUCT(BlueprintType)
struct FBPFriendInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	FString RealName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	EBPOnlinePresenceState OnlineState = EBPOnlinePresenceState::Offline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	FBPUniqueNetId UniqueNetId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	bool bIsPlayingSameGame = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
	FBPFriendPresenceInfo PresenceInfo;

	FBPFriendInfo()
	{
		OnlineState = EBPOnlinePresenceState::Offline;
		bIsPlayingSameGame = false;
	}
};
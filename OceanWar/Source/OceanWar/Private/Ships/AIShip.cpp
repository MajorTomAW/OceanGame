// Copyright © 2024 MajorT. All rights reserved.


#include "Ships/AIShip.h"

#include "EngineUtils.h"
#include "OceanityGameTags.h"
#include "AbilitySystem/OceanityAbilityComponent.h"
#include "AbilitySystem/OceanityAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Equipment/Components/OceanityEquipmentComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Ships/PlayerShip.h"
#include "Widgets/CommonExtendedActivatableWidget.h"


AAIShip::AAIShip()
{
	AbilitySystemComponent = CreateDefaultSubobject<UOceanityAbilityComponent>(TEXT("AbilitySystemComponent"));
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetIsReplicated(true);
		AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Minimal;	
	}
	
	AttributeSet = CreateDefaultSubobject<UOceanityAttributeSet>(TEXT("AttributeSet"));

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	if (HealthBarWidgetComponent)
	{
		HealthBarWidgetComponent->SetupAttachment(GetMesh());
		HealthBarWidgetComponent->SetDrawAtDesiredSize(true);
		HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	}
}

void AAIShip::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	BindToAttributeDelegates();
	if (UCommonExtendedActivatableWidget* Widget = Cast<UCommonExtendedActivatableWidget>(HealthBarWidgetComponent->GetUserWidgetObject()))
	{
		Widget->SetWidgetController(this);
		BroadcastInitialAttributes();
	}

	TimerDelegate.BindUObject(this, &ThisClass::ManageWidgetComponentVisibility);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.2f, true);
}

void AAIShip::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	BindFunctionsToEquipmentComponent();
	EquipmentComponent->InitActorEquipment(TurretClass, EngineClass, HullClass);
	Super::InitAbilityActorInfo();
}

void AAIShip::BroadcastInitialAttributes()
{
	if (UOceanityAttributeSet* AS = Cast<UOceanityAttributeSet>(AttributeSet))
	{
		for (auto& Pair : AS->TagsToAttributes)
		{
			OnAttributeValueChangedDelegate.Broadcast(Pair.Key, Pair.Value().GetNumericValue(AttributeSet));
		}
	}
}

void AAIShip::ManageWidgetComponentVisibility() const
{
	if (APlayerController* LocalPlayer = GetWorld()->GetFirstPlayerController())
	{
		if (APawn* PlayerPawn = LocalPlayer->GetPawnOrSpectator())
		{
			// Check if the player is within the widget's draw distance
			const float Distance = FVector::Dist(GetActorLocation(), PlayerPawn->GetActorLocation());
			const bool bInDrawDistance = Distance < MaxWidgetDrawDistance;

			if (!bInDrawDistance)
			{
				HealthBarWidgetComponent->SetHiddenInGame(true);
				return;
			}

			// Check if the player is within the widget's line of sight
			const FVector PawnCamLocation = PlayerPawn->GetComponentByClass<UCameraComponent>()->GetComponentLocation();
			FHitResult HitResult;
			FCollisionQueryParams TraceParams(FName(TEXT("VisibilityTrace")), true, this);
			TraceParams.bTraceComplex = true;
			TraceParams.bReturnPhysicalMaterial = false;
			TraceParams.AddIgnoredActor(PlayerPawn);
			TraceParams.AddIgnoredActor(this);

			if (GetWorld()->LineTraceSingleByChannel(HitResult, PawnCamLocation, GetActorLocation(), ECC_Visibility, TraceParams))
			{
				HealthBarWidgetComponent->SetHiddenInGame(true);
				return;
			}

			// If the player is within the widget's draw distance and line of sight, show the widget
			HealthBarWidgetComponent->SetHiddenInGame(false);
		}
	}
}


void AAIShip::BindToAttributeDelegates()
{
	if (UOceanityAttributeSet* AS = Cast<UOceanityAttributeSet>(AttributeSet))
	{
		for (auto& Pair : AS->TagsToAttributes)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
				[this, Pair](const FOnAttributeChangeData& Data)
				{
					OnAttributeValueChangedDelegate.Broadcast(Pair.Key, Pair.Value().GetNumericValue(AttributeSet));
				});
		}
	}
}


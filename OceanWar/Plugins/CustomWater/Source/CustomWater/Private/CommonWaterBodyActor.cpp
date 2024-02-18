// Copyright © 2024 MajorT. All rights reserved.
#include "CommonWaterBodyActor.h"

#include "WaterMeshComponent.h"
#include "WaterUtils.h"

#if WITH_EDITOR
#include "LevelEditor.h"
#endif

ACommonWaterBodyActor::ACommonWaterBodyActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	WaterMeshComponent = CreateDefaultSubobject<UWaterMeshComponent>("WaterMeshComponent");
	if (WaterMeshComponent)
	{
		SetRootComponent(WaterMeshComponent);
	}

#if WITH_EDITOR
	if (GIsEditor && !IsTemplate())
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorModule.OnActorSelectionChanged().AddUObject(this, &ThisClass::OnActorSelectionChanged);
	}
#endif
}

void ACommonWaterBodyActor::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	WaterMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void ACommonWaterBodyActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

UMaterialInstanceDynamic* ACommonWaterBodyActor::GetWaterMaterialInstance()
{
	CreateOrUpdateWaterMID();
	return WaterMaterialInstance;
}

void ACommonWaterBodyActor::CreateOrUpdateWaterMID()
{
	if (GetWorld())
	{
		WaterMaterialInstance = FWaterUtils::GetOrCreateTransientMID(WaterMaterialInstance, TEXT("WaterMID"), WaterMaterial, GetTransientMIDFlags());
	}
}

EObjectFlags ACommonWaterBodyActor::GetTransientMIDFlags() const
{
	return RF_Transient | RF_NonPIEDuplicateTransient | RF_TextExportTransient;
}

void ACommonWaterBodyActor::Update() const
{
	if (WaterMeshComponent)
	{
		WaterMeshComponent->Update();
	}
}

#if WITH_EDITOR
void ACommonWaterBodyActor::OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh)
{
	for (UObject* SelectedObject : NewSelection)
	{
		AActor* SelectedActor = Cast<AActor>(SelectedObject);

		if (SelectedActor)
		{
			WaterMeshComponent->MarkWaterMeshGridDirty();
		}
	}
}

void ACommonWaterBodyActor::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);
	WaterMeshComponent->MarkWaterMeshGridDirty();
}

void ACommonWaterBodyActor::PostEditUndo()
{
	Super::PostEditUndo();
	WaterMeshComponent->MarkWaterMeshGridDirty();
}

void ACommonWaterBodyActor::PostEditImport()
{
	Super::PostEditImport();
	WaterMeshComponent->MarkWaterMeshGridDirty();
}

void ACommonWaterBodyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	WaterMeshComponent->MarkWaterMeshGridDirty();
}
#endif

void ACommonWaterBodyActor::BeginPlay()
{
	Super::BeginPlay();
}


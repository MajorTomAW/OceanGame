// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommonWaterBodyActor.generated.h"

class UWaterMeshComponent;

UCLASS(Abstract)
class CUSTOMWATER_API ACommonWaterBodyActor : public AActor
{
	GENERATED_BODY()

public:
	ACommonWaterBodyActor();
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Water")
	TObjectPtr<UWaterMeshComponent> WaterMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	TObjectPtr<UMaterialInterface> WaterMaterial;

	UPROPERTY(VisibleInstanceOnly, Transient, NonPIEDuplicateTransient, TextExportTransient, meta = (DisplayAfter = "WaterMaterial"), Category = "Rendering")
	TObjectPtr<UMaterialInstanceDynamic> WaterMaterialInstance;

	UFUNCTION(BlueprintCallable, Category = "Water|Rendering")
	UMaterialInstanceDynamic* GetWaterMaterialInstance();

	UFUNCTION(BlueprintCallable, Category = "Water|Rendering")
	void CreateOrUpdateWaterMID();

	EObjectFlags GetTransientMIDFlags() const;

	void Update() const;

#if WITH_EDITOR
	void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);
	virtual void PostEditMove(bool bFinished) override;
	virtual void PostEditUndo() override;
	virtual void PostEditImport() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay() override;
};

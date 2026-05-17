#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridData.h"
#include "BuildingPlacementSystem.generated.h"

class ABuildingBase;
class UHTTPSGameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingPlaced, ABuildingBase*, Building);

// place one in the level — called from build menu
UCLASS()
class HTTPS_API ABuildingPlacementSystem : public AActor
{
	GENERATED_BODY()

public:
	ABuildingPlacementSystem();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnBuildingPlaced OnBuildingPlaced;

	UFUNCTION(BlueprintCallable)
	void StartPlacement(TSubclassOf<ABuildingBase> BuildingClass);

	// confirm on left click
	UFUNCTION(BlueprintCallable)
	void ConfirmPlacement();

	// cancel on right click / escape
	UFUNCTION(BlueprintCallable)
	void CancelPlacement();

	// rotate 90°
	UFUNCTION(BlueprintCallable)
	void RotatePlacement();

	UFUNCTION(BlueprintPure)
	bool IsPlacing() const { return bIsPlacing; }

	UFUNCTION(BlueprintPure)
	bool CanPlace() const { return bCanPlace; }

private:
	bool bIsPlacing = false;
	bool bCanPlace  = false;
	bool bRotated   = false;

	UPROPERTY()
	TObjectPtr<ABuildingBase> PreviewActor;

	TSubclassOf<ABuildingBase> PendingClass;
	FIntPoint CurrentFootprint;
	FIntPoint CurrentGridPos;

	void UpdatePreview();
	FIntPoint GetFootprintForClass(TSubclassOf<ABuildingBase> Class, bool bInRotated) const;
	FIntPoint GetCursorGridPos() const;
};

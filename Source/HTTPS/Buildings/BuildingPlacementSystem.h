#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingPlacementSystem.generated.h"

class ABuildingBase;
class UDomeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingPlaced, ABuildingBase*, Building);

// place one in the level, wire up Dome ref
UCLASS()
class HTTPS_API ABuildingPlacementSystem : public AActor
{
	GENERATED_BODY()

public:
	ABuildingPlacementSystem();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnBuildingPlaced OnBuildingPlaced;

	UPROPERTY(EditAnywhere, Category = "Placement")
	TObjectPtr<UDomeComponent> Dome;

	UFUNCTION(BlueprintCallable)
	void StartPlacement(TSubclassOf<ABuildingBase> BuildingClass);

	UFUNCTION(BlueprintCallable)
	void ConfirmPlacement();

	UFUNCTION(BlueprintCallable)
	void CancelPlacement();

	UFUNCTION(BlueprintPure)
	bool IsPlacing() const { return bIsPlacing; }

private:
	bool bIsPlacing = false;
	bool bCanPlace  = false;

	UPROPERTY()
	TObjectPtr<ABuildingBase> PreviewActor;

	TSubclassOf<ABuildingBase> PendingClass;

	FVector GetCursorWorldLocation() const;
	void UpdatePreview();
};

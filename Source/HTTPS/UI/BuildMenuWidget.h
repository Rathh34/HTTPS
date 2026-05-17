#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingBase.h"
#include "BuildMenuWidget.generated.h"

class ABuildingPlacementSystem;

UCLASS()
class HTTPS_API UBuildMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABuildingPlacementSystem> PlacementSystem;

	// called from BP button OnClicked
	UFUNCTION(BlueprintCallable)
	void SelectBuilding(TSubclassOf<ABuildingBase> BuildingClass);

	UFUNCTION(BlueprintCallable)
	void CancelSelection();

	UFUNCTION(BlueprintCallable)
	void RotateSelection();

	UFUNCTION(BlueprintCallable)
	void ConfirmSelection();

	// returns false if player cant afford it or research is missing
	UFUNCTION(BlueprintPure)
	bool CanBuild(TSubclassOf<ABuildingBase> BuildingClass) const;

	UFUNCTION(BlueprintPure)
	bool IsOpen() const { return bIsOpen; }

	UFUNCTION(BlueprintCallable)
	void SetOpen(bool bOpen);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnOpenChanged(bool bOpen);

private:
	bool bIsOpen = false;
};

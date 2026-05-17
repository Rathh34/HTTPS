#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingDetailsWidget.generated.h"

class ABuildingBase;

// shown when player clicks a building — hidden by default
UCLASS()
class HTTPS_API UBuildingDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ShowBuilding(ABuildingBase* Building);

	UFUNCTION(BlueprintCallable)
	void Hide();

	// assign one more drone from idle pool
	UFUNCTION(BlueprintCallable)
	void AssignDrone();

	// remove one drone and return it to idle pool
	UFUNCTION(BlueprintCallable)
	void UnassignDrone();

	// toggle energy on/off for this building
	UFUNCTION(BlueprintCallable)
	void ToggleEnergy();

	UFUNCTION(BlueprintPure)
	ABuildingBase* GetSelectedBuilding() const { return SelectedBuilding.Get(); }

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnBuildingSet(ABuildingBase* Building);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHide();

private:
	UPROPERTY()
	TObjectPtr<ABuildingBase> SelectedBuilding;
};

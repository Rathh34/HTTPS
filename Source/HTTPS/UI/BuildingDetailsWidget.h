#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingDetailsWidget.generated.h"

class ABuildingBase;
class AWorkforceManager;

// shown on building click — hidden by default
UCLASS()
class HTTPS_API UBuildingDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AWorkforceManager> WorkforceManager;

	UFUNCTION(BlueprintCallable)
	void ShowBuilding(ABuildingBase* Building);

	UFUNCTION(BlueprintCallable)
	void Hide();

	UFUNCTION(BlueprintCallable)
	void AssignWorker();

	UFUNCTION(BlueprintCallable)
	void UnassignWorker();

	UFUNCTION(BlueprintPure)
	ABuildingBase* GetSelectedBuilding() const { return SelectedBuilding.Get(); }

protected:
	// BP updates health bar, worker count etc when called
	UFUNCTION(BlueprintImplementableEvent)
	void OnBuildingSet(ABuildingBase* Building);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHide();

private:
	UPROPERTY()
	TObjectPtr<ABuildingBase> SelectedBuilding;
};

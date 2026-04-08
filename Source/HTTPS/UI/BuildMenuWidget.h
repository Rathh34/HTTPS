#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Buildings/BuildingBase.h"
#include "BuildMenuWidget.generated.h"

class ABuildingPlacementSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingSelected, TSubclassOf<ABuildingBase>, BuildingClass);

// BP handles button layout, C++ handles placement logic
UCLASS()
class HTTPS_API UBuildMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnBuildingSelected OnBuildingSelected;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABuildingPlacementSystem> PlacementSystem;

	UFUNCTION(BlueprintCallable)
	void SelectBuilding(TSubclassOf<ABuildingBase> BuildingClass);

	UFUNCTION(BlueprintCallable)
	void CancelSelection();

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

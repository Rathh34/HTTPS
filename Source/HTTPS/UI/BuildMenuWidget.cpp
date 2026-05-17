#include "BuildMenuWidget.h"
#include "BuildingPlacementSystem.h"
#include "BuildingData.h"
#include "HTTPSGameInstance.h"

void UBuildMenuWidget::SelectBuilding(TSubclassOf<ABuildingBase> BuildingClass)
{
	if (!BuildingClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BuildMenu] SelectBuilding called with null class"));
		return;
	}
	if (!PlacementSystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BuildMenu] PlacementSystem is null — not set in Event Construct"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[BuildMenu] Starting placement for %s"), *BuildingClass->GetName());
	PlacementSystem->StartPlacement(BuildingClass);
	SetOpen(false);
}

void UBuildMenuWidget::CancelSelection()
{
	if (PlacementSystem)
		PlacementSystem->CancelPlacement();
}

void UBuildMenuWidget::RotateSelection()
{
	if (PlacementSystem)
		PlacementSystem->RotatePlacement();
}

void UBuildMenuWidget::ConfirmSelection()
{
	if (PlacementSystem)
		PlacementSystem->ConfirmPlacement();
}

bool UBuildMenuWidget::CanBuild(TSubclassOf<ABuildingBase> BuildingClass) const
{
	if (!BuildingClass) return false;

	ABuildingBase* CDO = BuildingClass->GetDefaultObject<ABuildingBase>();
	if (!CDO || !CDO->BuildingData) return true;

	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return false;

	// check research unlock
	if (!GI->IsUnlocked(CDO->BuildingData->RequiredResearchTag)) return false;

	// check resources
	for (const FBuildingCost& Cost : CDO->BuildingData->BuildCost)
		if (!GI->HasResource(Cost.Type, Cost.Amount)) return false;

	return true;
}

void UBuildMenuWidget::SetOpen(bool bOpen)
{
	bIsOpen = bOpen;
	OnOpenChanged(bOpen);
}

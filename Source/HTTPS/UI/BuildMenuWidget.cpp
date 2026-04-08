#include "BuildMenuWidget.h"
#include "Buildings/BuildingPlacementSystem.h"

void UBuildMenuWidget::SelectBuilding(TSubclassOf<ABuildingBase> BuildingClass)
{
	if (!BuildingClass) return;

	if (PlacementSystem)
		PlacementSystem->StartPlacement(BuildingClass);

	OnBuildingSelected.Broadcast(BuildingClass);
	SetOpen(false);
}

void UBuildMenuWidget::CancelSelection()
{
	if (PlacementSystem)
		PlacementSystem->CancelPlacement();
}

void UBuildMenuWidget::SetOpen(bool bOpen)
{
	bIsOpen = bOpen;
	OnOpenChanged(bOpen);
}

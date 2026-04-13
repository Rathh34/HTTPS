#include "BuildMenuWidget.h"
#include "Buildings/BuildingPlacementSystem.h"

void UBuildMenuWidget::SelectBuilding(TSubclassOf<ABuildingBase> BuildingClass)
{
	if (!BuildingClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BuildMenu] SelectBuilding called with null BuildingClass"));
		return;
	}

	if (!PlacementSystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BuildMenu] PlacementSystem is null — not set in Event Construct"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[BuildMenu] Starting placement for %s"), *BuildingClass->GetName());
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
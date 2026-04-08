#include "BuildingDetailsWidget.h"
#include "Buildings/BuildingBase.h"
#include "Colonists/WorkforceManager.h"

void UBuildingDetailsWidget::ShowBuilding(ABuildingBase* Building)
{
	if (!Building) return;
	SelectedBuilding = Building;
	SetVisibility(ESlateVisibility::Visible);
	OnBuildingSet(Building);
}

void UBuildingDetailsWidget::Hide()
{
	SelectedBuilding = nullptr;
	SetVisibility(ESlateVisibility::Collapsed);
	OnHide();
}

void UBuildingDetailsWidget::AssignWorker()
{
	if (!WorkforceManager || !SelectedBuilding) return;
	WorkforceManager->AssignColonistTo(SelectedBuilding);
	OnBuildingSet(SelectedBuilding); // refresh BP display
}

void UBuildingDetailsWidget::UnassignWorker()
{
	if (!WorkforceManager || !SelectedBuilding) return;
	WorkforceManager->UnassignFromWorkplace(SelectedBuilding);
	OnBuildingSet(SelectedBuilding);
}

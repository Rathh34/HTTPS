#include "BuildingDetailsWidget.h"
#include "BuildingBase.h"
#include "DroneComponent.h"
#include "EnergyComponent.h"

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

void UBuildingDetailsWidget::AssignDrone()
{
	if (!SelectedBuilding) return;
	SelectedBuilding->DroneComp->AssignDrones(1);
	OnBuildingSet(SelectedBuilding); // refresh BP display
}

void UBuildingDetailsWidget::UnassignDrone()
{
	if (!SelectedBuilding || SelectedBuilding->DroneComp->AssignedDrones <= 0) return;
	SelectedBuilding->DroneComp->UnassignAll();
	// @note: unassigns all for simplicity — TODO: unassign one at a time
	OnBuildingSet(SelectedBuilding);
}

void UBuildingDetailsWidget::ToggleEnergy()
{
	if (!SelectedBuilding) return;
	UEnergyComponent* EC = SelectedBuilding->EnergyComp;
	EC->SetEnergyActive(!EC->bActive);
	OnBuildingSet(SelectedBuilding);
}

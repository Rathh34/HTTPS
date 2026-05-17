#include "DroneComponent.h"
#include "HTTPSGameInstance.h"
#include "Engine/World.h"

UDroneComponent::UDroneComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDroneComponent::EndPlay(const EEndPlayReason::Type Reason)
{
	UnassignAll();
	Super::EndPlay(Reason);
}

int32 UDroneComponent::AssignDrones(int32 Count)
{
	if (MaxDrones <= 0) return 0;

	const int32 CanTake = FMath::Min(Count, MaxDrones - AssignedDrones);
	if (CanTake <= 0) return 0;

	UHTTPSGameInstance* GI = GetWorld()->GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return 0;

	const int32 Actual = GI->AssignDrones(CanTake);
	AssignedDrones += Actual;
	OnAssignmentChanged.Broadcast(AssignedDrones, MaxDrones);
	return Actual;
}

void UDroneComponent::UnassignAll()
{
	if (AssignedDrones <= 0) return;

	UHTTPSGameInstance* GI = GetWorld() ? GetWorld()->GetGameInstance<UHTTPSGameInstance>() : nullptr;
	if (GI) GI->UnassignDrones(AssignedDrones);

	AssignedDrones = 0;
	OnAssignmentChanged.Broadcast(0, MaxDrones);
}

float UDroneComponent::GetEfficiency() const
{
	if (MaxDrones <= 0) return 1.f; // buildings with no drones run at 100%
	return FMath::Clamp((float)AssignedDrones / MaxDrones, 0.f, 1.f);
}

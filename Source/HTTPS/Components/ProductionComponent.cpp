#include "ProductionComponent.h"
#include "DroneComponent.h"
#include "HTTPSGameInstance.h"
#include "Engine/World.h"

UProductionComponent::UProductionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UProductionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bEnabled || BaseProductionRate <= 0.f) return;

	// lazy-cache drone comp from owner
	if (!DroneComp)
		DroneComp = GetOwner() ? GetOwner()->FindComponentByClass<UDroneComponent>() : nullptr;

	const float Efficiency = DroneComp ? DroneComp->GetEfficiency() : 1.f;
	if (Efficiency <= 0.f) return;

	UHTTPSGameInstance* GI = GetWorld()->GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;

	// blackout stops all production
	if (GI->bBlackout) return;

	GI->AddResource(ProducedResource, BaseProductionRate * Efficiency * DeltaTime);
}

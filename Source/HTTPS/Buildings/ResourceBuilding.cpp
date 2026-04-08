#include "ResourceBuilding.h"
#include "Resources/ResourceManager.h"

AResourceBuilding::AResourceBuilding()
{
	MaxHealth        = 200.f;
	MaxWorkers       = 3;
	PowerConsumption = 8.f;
}

void AResourceBuilding::OnOperationalTick(float DeltaTime)
{
	if (!ResourceManager) return;
	ResourceManager->AddResource(ProducedResource, YieldPerWorkerPerSecond * AssignedWorkers.Num() * DeltaTime);
}

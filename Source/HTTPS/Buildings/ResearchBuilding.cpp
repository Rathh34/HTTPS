#include "ResearchBuilding.h"
#include "Resources/ResourceManager.h"
#include "Resources/ResourceType.h"

AResearchBuilding::AResearchBuilding()
{
	MaxHealth        = 150.f;
	MaxWorkers       = 3;
	PowerConsumption = 12.f;
}

void AResearchBuilding::OnOperationalTick(float DeltaTime)
{
	if (!ResourceManager) return;
	ResourceManager->AddResource(EResourceType::ResearchPoints, ResearchPointsPerWorkerPerSecond * AssignedWorkers.Num() * DeltaTime);
}

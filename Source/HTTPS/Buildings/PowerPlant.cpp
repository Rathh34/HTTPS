#include "PowerPlant.h"
#include "Resources/ResourceManager.h"
#include "Resources/ResourceType.h"

APowerPlant::APowerPlant()
{
	MaxHealth        = 300.f;
	MaxWorkers       = 2;
	PowerConsumption = 0.f; // produces power, doesnt consume it
}

void APowerPlant::OnOperationalTick(float DeltaTime)
{
	if (!ResourceManager) return;
	ResourceManager->AddResource(EResourceType::Power, PowerOutputPerWorker * AssignedWorkers.Num() * DeltaTime);
}

#include "ProductionBuilding.h"
#include "ProductionComponent.h"

AProductionBuilding::AProductionBuilding()
{
	ProductionComp = CreateDefaultSubobject<UProductionComponent>(TEXT("ProductionComp"));
}

void AProductionBuilding::BeginPlay()
{
	Super::BeginPlay();

	// pull production values from data asset
	if (BuildingData)
	{
		ProductionComp->ProducedResource   = BuildingData->ProducedResource;
		ProductionComp->BaseProductionRate = BuildingData->ProductionRate;
	}

	// disabled until operational
	ProductionComp->SetEnabled(false);
}

void AProductionBuilding::OnOperational()
{
	ProductionComp->SetEnabled(true);
}

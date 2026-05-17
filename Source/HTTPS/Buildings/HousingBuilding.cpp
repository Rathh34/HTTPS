#include "HousingBuilding.h"
#include "HTTPSGameInstance.h"

void AHousingBuilding::OnOperational()
{
	if (!BuildingData) return;
	if (UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>())
		GI->AddHousingCapacity(BuildingData->HousingCapacity);
}

void AHousingBuilding::EndPlay(const EEndPlayReason::Type Reason)
{
	// give capacity back when building destroyed
	if (BuildingData)
		if (UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>())
			GI->RemoveHousingCapacity(BuildingData->HousingCapacity);

	Super::EndPlay(Reason);
}

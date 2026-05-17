#include "HappinessBuilding.h"
#include "HTTPSGameInstance.h"

void AHappinessBuilding::OnOperational()
{
	if (!BuildingData) return;
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;

	GI->AddHappiness(EHappinessType::Comfort,       BuildingData->ComfortBonus);
	GI->AddHappiness(EHappinessType::Amusement,     BuildingData->AmusementBonus);
	GI->AddHappiness(EHappinessType::Satisfaction,  BuildingData->SatisfactionBonus);
}

void AHappinessBuilding::EndPlay(const EEndPlayReason::Type Reason)
{
	if (BuildingData)
	{
		UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
		if (GI)
		{
			GI->RemoveHappiness(EHappinessType::Comfort,      BuildingData->ComfortBonus);
			GI->RemoveHappiness(EHappinessType::Amusement,    BuildingData->AmusementBonus);
			GI->RemoveHappiness(EHappinessType::Satisfaction, BuildingData->SatisfactionBonus);
		}
	}
	Super::EndPlay(Reason);
}

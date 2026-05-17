#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "HousingBuilding.generated.h"

// prefab, immeuble, gratte-ciel all use this — capacity driven by data asset
UCLASS()
class HTTPS_API AHousingBuilding : public ABuildingBase
{
	GENERATED_BODY()

protected:
	virtual void OnOperational() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;
};

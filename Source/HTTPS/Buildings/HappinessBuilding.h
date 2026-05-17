#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "HappinessBuilding.generated.h"

// parc, jardin, centre VR/AR/commercial, routes — adds C/A/S from data asset
UCLASS()
class HTTPS_API AHappinessBuilding : public ABuildingBase
{
	GENERATED_BODY()

protected:
	virtual void OnOperational() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;
};

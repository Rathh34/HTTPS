#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "HousingBuilding.generated.h"

// no workers needed, just raises the population cap
UCLASS()
class HTTPS_API AHousingBuilding : public ABuildingBase
{
	GENERATED_BODY()

public:
	AHousingBuilding();

	// @note: not yet wired into ColonistSpawner arrival cap
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Housing")
	int32 HousingCapacity = 20;
};

#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "DomeBuilding.generated.h"

// the dome itself — upgrading expands the interior grid
UCLASS()
class HTTPS_API ADomeBuilding : public ABuildingBase
{
	GENERATED_BODY()

public:
	// 13 for Mark I, 18 for Mark II, set per data asset in BP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dome")
	int32 InteriorSize = 13;

protected:
	virtual void OnOperational() override;
};

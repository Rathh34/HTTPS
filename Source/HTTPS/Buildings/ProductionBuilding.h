#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "ProductionBuilding.generated.h"

class UProductionComponent;

// resource harvesters, factories, biomasse buildings — all driven by data asset + ProductionComponent
UCLASS()
class HTTPS_API AProductionBuilding : public ABuildingBase
{
	GENERATED_BODY()

public:
	AProductionBuilding();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProductionComponent> ProductionComp;

protected:
	virtual void BeginPlay() override;
	virtual void OnOperational() override;
};

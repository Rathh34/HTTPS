#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "ResearchBuilding.generated.h"

class AResourceManager;

UCLASS()
class HTTPS_API AResearchBuilding : public ABuildingBase
{
	GENERATED_BODY()

public:
	AResearchBuilding();

	UPROPERTY(EditAnywhere, Category = "Research")
	float ResearchPointsPerWorkerPerSecond = 1.f;

	UPROPERTY(EditAnywhere, Category = "Research")
	TObjectPtr<AResourceManager> ResourceManager;

protected:
	virtual void OnOperationalTick(float DeltaTime) override;
};

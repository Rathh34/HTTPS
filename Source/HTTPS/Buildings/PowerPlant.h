#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "PowerPlant.generated.h"

class AResourceManager;

UCLASS()
class HTTPS_API APowerPlant : public ABuildingBase
{
	GENERATED_BODY()

public:
	APowerPlant();

	UPROPERTY(EditAnywhere, Category = "Power")
	float PowerOutputPerWorker = 20.f;

	UPROPERTY(EditAnywhere, Category = "Power")
	TObjectPtr<AResourceManager> ResourceManager;

protected:
	virtual void OnOperationalTick(float DeltaTime) override;
};

#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "Resources/ResourceType.h"
#include "ResourceBuilding.generated.h"

class AResourceManager;

// generic resource producer — configure ProducedResource per building in editor
UCLASS()
class HTTPS_API AResourceBuilding : public ABuildingBase
{
	GENERATED_BODY()

public:
	AResourceBuilding();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	EResourceType ProducedResource = EResourceType::Metal;

	UPROPERTY(EditAnywhere, Category = "Resource")
	float YieldPerWorkerPerSecond = 2.f;

	UPROPERTY(EditAnywhere, Category = "Resource")
	TObjectPtr<AResourceManager> ResourceManager;

protected:
	virtual void OnOperationalTick(float DeltaTime) override;
};

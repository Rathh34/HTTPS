#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "DroneFactory.generated.h"

// produces drones on a timer scaled by drone efficiency
UCLASS()
class HTTPS_API ADroneFactory : public ABuildingBase
{
	GENERATED_BODY()

public:
	ADroneFactory();

	// seconds per drone at 100% efficiency — default 60s (1min) for usine, 20s for manufacture
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Factory")
	float ProductionInterval = 60.f;

protected:
	virtual void OnOperational() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

private:
	FTimerHandle ProductionTimer;

	UFUNCTION()
	void ProduceDrone();
};

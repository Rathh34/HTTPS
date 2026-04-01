#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColonistSpawner.generated.h"

class AColonist;
class AWorkforceManager;

UCLASS()
class HTTPS_API AColonistSpawner : public AActor
{
	GENERATED_BODY()

public:
	AColonistSpawner();

	// base arrivals per week at 50 reputation — scales linearly
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int32 BaseWeeklyArrivals = 10;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AColonist> ColonistClass;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TObjectPtr<AWorkforceManager> WorkforceManager;

	// called by WeekManager each week
	UFUNCTION(BlueprintCallable)
	void OnWeekElapsed();

private:
	int32 CalculateArrivals() const;
};
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

	// arrivals at rep 50 — scales linearly, 0 rep = 0 arrivals, 100 rep = 2x
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int32 BaseWeeklyArrivals = 10;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AColonist> ColonistClass;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TObjectPtr<AWorkforceManager> WorkforceManager;

	UFUNCTION(BlueprintCallable)
	void OnWeekElapsed();

private:
	int32 CalculateArrivals() const;
};

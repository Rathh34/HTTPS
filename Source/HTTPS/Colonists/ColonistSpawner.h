#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColonistSpawner.generated.h"

class AColonist;
class AWorkforceManager;

// runs a weekly timer and sends colonists based on current reputation
// place one in the level and hook up the WorkforceManager ref
UCLASS()
class HTTPS_API AColonistSpawner : public AActor
{
	GENERATED_BODY()

public:
	AColonistSpawner();

	virtual void BeginPlay() override;

	// how many real seconds = one in-game week
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float WeekDuration = 60.f;

	// base arrivals per week at exactly 50 reputation
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int32 BaseWeeklyArrivals = 10;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AColonist> ColonistClass;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TObjectPtr<AWorkforceManager> WorkforceManager;

private:
	FTimerHandle WeekTimerHandle;

	void OnWeekElapsed();
	int32 CalculateArrivals() const; // scales linearly with reputation
};
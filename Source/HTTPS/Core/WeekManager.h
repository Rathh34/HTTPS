#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeekManager.generated.h"

class AColonistSpawner;
class AReputationManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeekPassed, int32, WeekNumber);

// owns the week timer and calls everything in the right order each week
// place one in the level and wire up the refs
UCLASS()
class HTTPS_API AWeekManager : public AActor
{
	GENERATED_BODY()

public:
	AWeekManager();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnWeekPassed OnWeekPassed;

	// how many real seconds = one in-game week
	UPROPERTY(EditAnywhere, Category = "Week")
	float WeekDuration = 60.f;

	UPROPERTY(EditAnywhere, Category = "Week")
	TObjectPtr<AColonistSpawner> ColonistSpawner;

	UPROPERTY(EditAnywhere, Category = "Week")
	TObjectPtr<AReputationManager> ReputationManager;

private:
	FTimerHandle WeekTimerHandle;

	void OnWeekElapsed();
};
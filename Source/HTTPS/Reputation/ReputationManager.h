#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GovernmentObjective.h"
#include "ReputationManager.generated.h"

class AResourceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveUpdated, const FGovernmentObjective&, Objective);

UCLASS()
class HTTPS_API AReputationManager : public AActor
{
	GENERATED_BODY()

public:
	AReputationManager();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnObjectiveCompleted;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveUpdated OnObjectiveFailed;

	UPROPERTY(EditAnywhere, Category = "Reputation")
	TObjectPtr<AResourceManager> ResourceManager;

	// called by WeekManager each week
	UFUNCTION(BlueprintCallable)
	void OnWeekPassed();

	UFUNCTION(BlueprintPure)
	const FGovernmentObjective& GetCurrentObjective() const { return CurrentObjective; }

private:
	FGovernmentObjective CurrentObjective;
	int32 WeekIssuedOn = 0;

	void IssueNewObjective();
	bool EvaluateObjective() const;
};
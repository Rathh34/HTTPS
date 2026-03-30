#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkforceManager.generated.h"

class AColonist;

// fired when idle count changes — UI binds to this to show available workers
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorkforceChanged, int32, IdleCount);

UCLASS()
class HTTPS_API AWorkforceManager : public AActor
{
	GENERATED_BODY()

public:
	AWorkforceManager();

	UPROPERTY(BlueprintAssignable)
	FOnWorkforceChanged OnWorkforceChanged;

	// called by ColonistSpawner when new colonists arrive
	UFUNCTION(BlueprintCallable)
	void RegisterColonist(AColonist* Colonist);

	// assigns the first available idle colonist to a workplace, returns false if none
	UFUNCTION(BlueprintCallable)
	bool AssignColonistTo(AActor* Workplace);

	// frees all colonists working at the given workplace
	UFUNCTION(BlueprintCallable)
	void UnassignFromWorkplace(AActor* Workplace);

	UFUNCTION(BlueprintPure)
	int32 GetIdleCount() const;

	UFUNCTION(BlueprintPure)
	int32 GetTotalCount() const { return AllColonists.Num(); }

	UFUNCTION(BlueprintPure)
	TArray<AColonist*> GetAllColonists() const;

private:
	UPROPERTY()
	TArray<TObjectPtr<AColonist>> AllColonists;

	AColonist* FindIdleColonist() const;
};
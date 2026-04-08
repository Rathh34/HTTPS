#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkforceManager.generated.h"

class AColonist;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorkforceChanged, int32, IdleCount);

UCLASS()
class HTTPS_API AWorkforceManager : public AActor
{
	GENERATED_BODY()

public:
	AWorkforceManager();

	UPROPERTY(BlueprintAssignable)
	FOnWorkforceChanged OnWorkforceChanged;

	UFUNCTION(BlueprintCallable)
	void RegisterColonist(AColonist* Colonist);

	// assigns first idle colonist to Workplace, returns false if none available
	UFUNCTION(BlueprintCallable)
	bool AssignColonistTo(AActor* Workplace);

	UFUNCTION(BlueprintCallable)
	void UnassignFromWorkplace(AActor* Workplace);

	UFUNCTION(BlueprintPure)
	int32 GetIdleCount() const;

	UFUNCTION(BlueprintPure)
	int32 GetTotalCount() const { return AllColonists.Num(); }

	// @note: returns raw ptrs — cant expose TObjectPtr to UHT
	UFUNCTION(BlueprintPure)
	TArray<AColonist*> GetAllColonists() const;

private:
	UPROPERTY()
	TArray<TObjectPtr<AColonist>> AllColonists;

	AColonist* FindIdleColonist() const;
};

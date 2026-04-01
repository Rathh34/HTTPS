#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceType.h"
#include "ResourceManager.h"
#include "ResourceNode.generated.h"

class AColonist;

UCLASS()
class HTTPS_API AResourceNode : public AActor
{
	GENERATED_BODY()

public:
	AResourceNode();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	EResourceType ResourceType = EResourceType::Metal;

	UPROPERTY(EditAnywhere, Category = "Resource")
	float YieldPerWorkerPerSecond = 1.f;

	UPROPERTY(EditAnywhere, Category = "Resource")
	int32 MaxWorkers = 3;

	UPROPERTY(EditAnywhere, Category = "Resource")
	float MaxReserve = 5000.f;

	// place this in the level and assign it
	UPROPERTY(EditAnywhere, Category = "Resource")
	TObjectPtr<AResourceManager> ResourceManager;

	UFUNCTION(BlueprintCallable)
	bool AssignWorker(AColonist* Colonist);

	UFUNCTION(BlueprintCallable)
	void RemoveWorker(AColonist* Colonist);

	UFUNCTION(BlueprintPure)
	int32 GetWorkerCount() const { return AssignedWorkers.Num(); }

	UFUNCTION(BlueprintPure)
	float GetReservePercent() const { return CurrentReserve / MaxReserve; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<TObjectPtr<AColonist>> AssignedWorkers;

	float CurrentReserve = 0.f;
};
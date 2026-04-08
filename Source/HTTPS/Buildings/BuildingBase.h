#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IDamageable.h"
#include "BuildingBase.generated.h"

class AColonist;

UENUM(BlueprintType)
enum class EBuildingState : uint8
{
	Constructing,
	Operational,
	Damaged,
	Destroyed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingStateChanged, EBuildingState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWorkerChanged, AColonist*, Colonist, bool, bAssigned);

UCLASS(Abstract)
class HTTPS_API ABuildingBase : public AActor, public IDamageable
{
	GENERATED_BODY()

public:
	ABuildingBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	float MaxHealth = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	int32 MaxWorkers = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	float PowerConsumption = 5.f;

	UPROPERTY(BlueprintReadOnly)
	EBuildingState State = EBuildingState::Constructing;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth = 200.f;

	UPROPERTY(BlueprintAssignable)
	FOnBuildingStateChanged OnStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnWorkerChanged OnWorkerChanged;

	UFUNCTION(BlueprintCallable)
	bool AssignWorker(AColonist* Colonist);

	UFUNCTION(BlueprintCallable)
	void RemoveWorker(AColonist* Colonist);

	UFUNCTION(BlueprintPure)
	int32 GetWorkerCount() const { return AssignedWorkers.Num(); }

	UFUNCTION(BlueprintPure)
	bool IsOperational() const { return State == EBuildingState::Operational; }

	// IDamageable
	virtual void ApplyDamage_Implementation(float Amount, AActor* DamageSource) override;
	virtual float GetCurrentHealth_Implementation() const override { return CurrentHealth; }
	virtual bool IsAlive_Implementation() const override { return State != EBuildingState::Destroyed; }

protected:
	UPROPERTY()
	TArray<TObjectPtr<AColonist>> AssignedWorkers;

	void SetState(EBuildingState NewState);

	// override for production logic
	virtual void OnOperationalTick(float DeltaTime) {}
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DroneComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDroneAssignmentChanged, int32, Assigned, int32, Max);

// handles drone assignment for one building — efficiency = assigned/max
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HTTPS_API UDroneComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDroneComponent();

	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drones")
	int32 MaxDrones = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 AssignedDrones = 0;

	UPROPERTY(BlueprintAssignable)
	FOnDroneAssignmentChanged OnAssignmentChanged;

	// tries to assign Count drones from GameInstance idle pool
	UFUNCTION(BlueprintCallable)
	int32 AssignDrones(int32 Count);

	// returns all assigned drones to the idle pool
	UFUNCTION(BlueprintCallable)
	void UnassignAll();

	UFUNCTION(BlueprintPure)
	float GetEfficiency() const;

	UFUNCTION(BlueprintPure)
	bool IsFullyStaffed() const { return AssignedDrones >= MaxDrones; }
};

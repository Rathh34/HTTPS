#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingData.h"
#include "BuildingBase.generated.h"

class UHealthComponent;
class UDroneComponent;
class UEnergyComponent;
class UHTTPSGameInstance;

UENUM(BlueprintType)
enum class EBuildingState : uint8
{
	Constructing,
	Operational,
	Destroyed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingStateChanged, EBuildingState, NewState);

UCLASS(Abstract)
class HTTPS_API ABuildingBase : public AActor
{
	GENERATED_BODY()

public:
	ABuildingBase();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDroneComponent> DroneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UEnergyComponent> EnergyComp;

	// set per subclass in constructor — editor also shows it
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	TObjectPtr<UBuildingData> BuildingData;

	UPROPERTY(BlueprintReadOnly)
	EBuildingState State = EBuildingState::Constructing;

	UPROPERTY(BlueprintReadOnly)
	FIntPoint GridOrigin = FIntPoint::ZeroValue;

	// set on placement, includes rotation
	UPROPERTY(BlueprintReadOnly)
	FIntPoint GridFootprint = FIntPoint(1, 1);

	UPROPERTY(BlueprintReadOnly)
	bool bRotated = false;

	UPROPERTY(BlueprintAssignable)
	FOnBuildingStateChanged OnStateChanged;

	UFUNCTION(BlueprintCallable)
	void SetOperational();

	UFUNCTION(BlueprintPure)
	bool IsOperational() const { return State == EBuildingState::Operational; }

	// called by placement system after spawn
	UFUNCTION(BlueprintCallable)
	void OnPlaced(FIntPoint Origin, bool bInRotated);

protected:
	void SetState(EBuildingState NewState);

	// override in subclasses for building-specific operational logic
	virtual void OnOperational() {}

private:
	UFUNCTION()
	void OnDied();
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceType.h"
#include "ResourceDeposit.generated.h"

// placed by level designer — registers its tile as ResourceDeposit on BeginPlay
// drones can be assigned directly to harvest it
UCLASS()
class HTTPS_API AResourceDeposit : public AActor
{
	GENERATED_BODY()

public:
	AResourceDeposit();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deposit")
	EResourceType ResourceType = EResourceType::Acier;

	// 10000 for acier, 2500 for quartz per GDD
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deposit")
	float MaxReserve = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deposit")
	float BaseYieldPerDronePerSecond = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deposit")
	int32 MaxDrones = 10;

	UPROPERTY(BlueprintReadOnly)
	float CurrentReserve = 0.f;

	UPROPERTY(BlueprintReadOnly)
	int32 AssignedDrones = 0;

	// depleted when a synthétiseur is built — set by GDD unlock
	UPROPERTY(BlueprintReadWrite)
	bool bInfiniteReserve = false;

	UFUNCTION(BlueprintCallable)
	int32 AssignDrones(int32 Count);

	UFUNCTION(BlueprintCallable)
	void UnassignDrones(int32 Count);

	UFUNCTION(BlueprintPure)
	float GetReservePercent() const { return CurrentReserve / MaxReserve; }
};

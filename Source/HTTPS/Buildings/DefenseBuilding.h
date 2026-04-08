#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "DefenseBuilding.generated.h"

// needs workers to fire — no workers = idle
UCLASS()
class HTTPS_API ADefenseBuilding : public ABuildingBase
{
	GENERATED_BODY()

public:
	ADefenseBuilding();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Defense")
	float AttackRange = 1500.f;

	UPROPERTY(EditAnywhere, Category = "Defense")
	float DamagePerSecond = 15.f;

	UPROPERTY(EditAnywhere, Category = "Defense")
	float FireRate = 1.f;

private:
	float TimeSinceLastAttack = 0.f;

	AActor* FindTargetInRange() const;
};

#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "DefenseBuilding.generated.h"

class ANativeBase;

// tourelle automatique + canon à plasma both use this
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
	float DamagePerShot = 1.f;

	UPROPERTY(EditAnywhere, Category = "Defense")
	float FireRate = 2.f; // shots per second

	// plasma canon: first hit + penetration damage
	UPROPERTY(EditAnywhere, Category = "Defense")
	float PenetrationDamage = 0.f;

protected:
	virtual void BeginPlay() override;

private:
	float TimeSinceLastShot = 0.f;

	ANativeBase* FindTargetInRange() const;
};

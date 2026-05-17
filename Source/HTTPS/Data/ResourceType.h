#pragma once

#include "CoreMinimal.h"
#include "ResourceType.generated.h"

// energy is NOT a resource — it's a production/consumption balance tracked separately
UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Acier,
	Quartz,
	Or,
	Biomasse,
	CadavreAlien
};

UENUM(BlueprintType)
enum class ETileState : uint8
{
	Empty,
	Occupied,
	DomeInterior,  // buildable, interior buildings only
	DomeWall,      // unbuildable ring around dome
	DomeExterior,  // buildable, exterior buildings only
	ResourceDeposit
};

UENUM(BlueprintType)
enum class ETileZone : uint8
{
	Interior,
	Exterior,
	Both  // roads, BB
};

UENUM(BlueprintType)
enum class EMissionType : uint8
{
	HarvestResource,
	BuildBuilding,
	KillAliens,
	ReachPopulation
};

UENUM(BlueprintType)
enum class EHappinessType : uint8
{
	Comfort,
	Amusement,
	Satisfaction
};

#pragma once

#include "CoreMinimal.h"
#include "ResourceType.generated.h"

// everything that can be stored and consumed in the game
UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Oxygen,
	Power,
	Food,
	Metal,
	RareMineral,  
	ResearchPoints
};
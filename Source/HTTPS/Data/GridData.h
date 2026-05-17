#pragma once

#include "CoreMinimal.h"
#include "ResourceType.h"
#include "GridData.generated.h"

class ABuildingBase;

USTRUCT(BlueprintType)
struct FGridTile
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	ETileState State = ETileState::Empty;

	// null if unoccupied
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABuildingBase> Occupant = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FIntPoint Coords = FIntPoint::ZeroValue;

	// for multi-tile buildings, points to the placement origin tile
	UPROPERTY(BlueprintReadOnly)
	FIntPoint OriginCoords = FIntPoint::ZeroValue;
};

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ResourceType.h"
#include "BuildingData.generated.h"

USTRUCT(BlueprintType)
struct FBuildingCost
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EResourceType Type = EResourceType::Acier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Amount = 0.f;
};

// all per-building config lives here — set in editor, read by buildings and UI
UCLASS(BlueprintType)
class HTTPS_API UBuildingData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cost")
	TArray<FBuildingCost> BuildCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cost")
	float BuildTime = 10.f;

	// positive = produces energy, negative = consumes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy")
	float EnergyDelta = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drones")
	int32 MaxDrones = 0;

	// footprint before rotation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Placement")
	FIntPoint FootprintSize = FIntPoint(1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Placement")
	ETileZone RequiredZone = ETileZone::Interior;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MaxHealth = 100.f;

	// --- production ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Production")
	EResourceType ProducedResource = EResourceType::Acier;

	// per second at 100% drone efficiency
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Production")
	float ProductionRate = 0.f;

	// --- housing ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Housing")
	int32 HousingCapacity = 0;

	// --- happiness ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Happiness")
	float ComfortBonus = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Happiness")
	float AmusementBonus = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Happiness")
	float SatisfactionBonus = 0.f;

	// research tag required to build — empty = always available
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Research")
	FName RequiredResearchTag;
};

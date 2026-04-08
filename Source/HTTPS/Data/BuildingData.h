#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Resources/ResourceType.h"
#include "BuildingData.generated.h"

USTRUCT(BlueprintType)
struct FResourceCost
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EResourceType Type = EResourceType::Metal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Amount = 0.f;
};

// drive building config from data assets rather than hardcoded defaults
UCLASS(BlueprintType)
class HTTPS_API UBuildingData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FResourceCost> BuildCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxWorkers = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PowerConsumption = 0.f;
};

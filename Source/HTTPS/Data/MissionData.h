#pragma once

#include "CoreMinimal.h"
#include "ResourceType.h"
#include "MissionData.generated.h"

USTRUCT(BlueprintType)
struct FMissionData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	EMissionType Type = EMissionType::HarvestResource;

	UPROPERTY(BlueprintReadOnly)
	FText Description;

	// used when Type == HarvestResource
	UPROPERTY(BlueprintReadOnly)
	EResourceType ResourceType = EResourceType::Acier;

	// target count / amount depending on type
	UPROPERTY(BlueprintReadOnly)
	float TargetValue = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentProgress = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float RepReward = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted = false;
};

// weekly reward based on rep tier
USTRUCT(BlueprintType)
struct FRepTierReward
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RepThreshold = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float OrReward = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PopReward = 0;
};

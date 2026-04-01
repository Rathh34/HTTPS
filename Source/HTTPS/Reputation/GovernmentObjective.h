#pragma once

#include "CoreMinimal.h"
#include "HTTPS/Resources/ResourceType.h"
#include "GovernmentObjective.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	ReachPopulation,
	ProduceResource,
	MaintainReputation
};

USTRUCT(BlueprintType)
struct FGovernmentObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EObjectiveType Type = EObjectiveType::ReachPopulation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	// target value (population, resource amount, or reputation floor)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TargetValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EResourceType ResourceType = EResourceType::Metal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ReputationReward = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ReputationPenalty = -15.f;

	// weeks from issue date to deadline
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 WeekDeadline = 4;

	UPROPERTY(BlueprintReadOnly)
	bool bCompleted = false;

	UPROPERTY(BlueprintReadOnly)
	bool bFailed = false;
};
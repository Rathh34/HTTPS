#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ResearchNode.generated.h"

// one node in the tech tree — set up as data asset, referenced by the tree asset
UCLASS(BlueprintType)
class HTTPS_API UResearchNode : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GoldCost = 0.f;

	// minimum population to unlock
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RequiredPopulation = 0;

	// tag granted on unlock — checked by BuildingData.RequiredResearchTag and GameInstance.IsUnlocked
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName UnlockTag;

	// tags of nodes that must be unlocked first
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> Prerequisites;
};

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ResearchTree.generated.h"

class UResearchNode;

// assign in editor, reference from ResearchManager
UCLASS(BlueprintType)
class HTTPS_API UResearchTree : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UResearchNode>> AllNodes;

	// returns nodes with all prereqs met that arent unlocked yet
	UFUNCTION(BlueprintPure)
	TArray<UResearchNode*> GetAvailableNodes() const;
};

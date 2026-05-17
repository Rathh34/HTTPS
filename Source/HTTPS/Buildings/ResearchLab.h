#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "ResearchLab.generated.h"

// laboratoire + complexe scientifique — unlocks tech tree tiers
// actual research actions done via UI calling GameInstance->UnlockNode
// this building just registers as existing so UI can gate research tier
UCLASS()
class HTTPS_API AResearchLab : public ABuildingBase
{
	GENERATED_BODY()

public:
	// tiers this lab unlocks (0-3 for lab, 4-7 for complexe)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Research")
	TArray<int32> UnlockedTiers;

protected:
	virtual void OnOperational() override;
};

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveTrackerWidget.generated.h"

class AReputationManager;

UCLASS()
class HTTPS_API UObjectiveTrackerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AReputationManager> ReputationManager;

	// called by MainHUDWidget each week
	UFUNCTION(BlueprintCallable)
	void RefreshObjective();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnObjectiveRefreshed(const FText& Description, int32 WeeksRemaining, float Reputation);
};

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MissionData.h"
#include "MissionWidget.generated.h"

// shows active missions and progress — BP handles visual layout
UCLASS()
class HTTPS_API UMissionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// call from BP to force a refresh
	UFUNCTION(BlueprintCallable)
	void RefreshMissions();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnMissionsRefreshed(const TArray<FMissionData>& Missions);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMissionCompletedAnim(FMissionData Mission);

private:
	UFUNCTION()
	void OnMissionCompleted(FMissionData Mission);
};

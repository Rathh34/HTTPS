#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

class UBuildMenuWidget;
class UObjectiveTrackerWidget;
class UEventNotificationWidget;
class ABuildingPlacementSystem;
class AResourceManager;
class AWorkforceManager;

// root HUD widget — sub-widget names must match BindWidget property names exactly
UCLASS()
class HTTPS_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnWeekPassed(int32 WeekNumber);

	UFUNCTION(BlueprintCallable)
	void ShowEventNotification(UEventBase* Event);

	// BindWidget — variable names must match widget names in the BP designer exactly
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBuildMenuWidget> BuildMenu;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UObjectiveTrackerWidget> ObjectiveTracker;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEventNotificationWidget> EventNotification;

	// set from BP Event Construct via GetAllActorsOfClass
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AResourceManager> ResourceManager;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AWorkforceManager> WorkforceManager;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABuildingPlacementSystem> PlacementSystem;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void RefreshResourceDisplay(float Metal, float Power, float Food, float Oxygen, float RareMineral);

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshPopulationDisplay(int32 Population, float Reputation);

private:
	float RefreshInterval  = 0.2f; // dont push every tick, 5hz is plenty
	float TimeSinceRefresh = 0.f;
};

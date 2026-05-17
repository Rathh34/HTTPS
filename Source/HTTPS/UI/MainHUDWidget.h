#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

class UBuildMenuWidget;
class UBuildingDetailsWidget;
class UMissionWidget;
class UResearchWidget;
class UTimeControlWidget;
class UEventNotificationWidget;
class ABuildingPlacementSystem;

// root HUD — sub-widget variable names must match BindWidget property names exactly
UCLASS()
class HTTPS_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// BindWidget — names must match designer widget names exactly
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBuildMenuWidget> BuildMenu;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBuildingDetailsWidget> BuildingDetails;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UMissionWidget> MissionPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UResearchWidget> ResearchPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTimeControlWidget> TimeControls;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEventNotificationWidget> EventNotification;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABuildingPlacementSystem> PlacementSystem;

protected:
	// BP implements these to push fresh data to text blocks / progress bars
	UFUNCTION(BlueprintImplementableEvent)
	void RefreshResourceBar(float Acier, float Quartz, float Or, float Biomasse, float CadavreAlien);

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshEnergyBar(float Production, float Consumption, bool bBlackout);

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshDroneBar(int32 Total, int32 Assigned);

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshPopulationBar(int32 Population, int32 HousingCap, float HappinessPercent);

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshDate(int32 Day, int32 Week, int32 Month);

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshReputation(float Reputation);

	UFUNCTION(BlueprintImplementableEvent)
	void OnBlackoutStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void OnBlackoutRestored();

private:
	float RefreshInterval  = 0.2f; // 5hz is plenty for resource display
	float TimeSinceRefresh = 0.f;

	bool bWasBlackout = false;

	void BindToGameInstance();

	UFUNCTION()
	void OnWaveStarted(int32 WaveNumber, int32 WaveSize);
};

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ResourceType.h"
#include "GridData.h"
#include "MissionData.h"
#include "HTTPSGameInstance.generated.h"

class ABuildingBase;
class ANativeHorde;
class UResearchNode;

// --- delegates ---
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceChanged,    EResourceType, Type, float, NewAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnEnergyChanged,    float, Production, float, Consumption, bool, bBlackout);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDronesChanged,      int32, Total, int32, Assigned);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPopulationChanged,  int32, Population, int32, HousingCap);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHappinessChanged, float, Comfort, float, Amusement, float, Satisfaction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTimePassed,       int32, Day, int32, Week, int32, Month);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeekPassed,          int32, Week);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReputationChanged,   float, Reputation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionCompleted,    FMissionData, Mission);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeUnlocked,        FName, Tag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWaveStarted,        int32, WaveNumber, int32, WaveSize);

// everything lives here — no manager actors placed in level
UCLASS()
class HTTPS_API UHTTPSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UHTTPSGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	// called by GameMode once the level is ready — starts all timers
	UFUNCTION(BlueprintCallable)
	void StartGame();

	// ===================== GRID =====================

	// set in BP subclass of GameInstance
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 GridWidth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 GridHeight = 100;

	// world units per tile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	float TileSize = 200.f;

	UFUNCTION(BlueprintCallable)
	void InitGrid();

	UFUNCTION(BlueprintPure)
	FGridTile GetTile(FIntPoint Coords) const;

	UFUNCTION(BlueprintCallable)
	void SetTileState(FIntPoint Coords, ETileState NewState);

	UFUNCTION(BlueprintPure)
	bool IsTileValid(FIntPoint Coords) const;

	// checks all tiles in footprint are free and in the correct zone
	UFUNCTION(BlueprintPure)
	bool CanPlaceBuilding(FIntPoint Origin, FIntPoint Footprint, ETileZone Zone) const;

	UFUNCTION(BlueprintCallable)
	void OccupyTiles(FIntPoint Origin, FIntPoint Footprint, ABuildingBase* Building);

	UFUNCTION(BlueprintCallable)
	void FreeTiles(FIntPoint Origin, FIntPoint Footprint);

	// sets interior tiles for a dome of given size centered on map
	UFUNCTION(BlueprintCallable)
	void SetDomeSize(int32 InteriorSize);

	UFUNCTION(BlueprintPure)
	FVector GridToWorld(FIntPoint Coords) const;

	UFUNCTION(BlueprintPure)
	FIntPoint WorldToGrid(FVector WorldPos) const;

	// ===================== RESOURCES =====================

	UPROPERTY(BlueprintAssignable)
	FOnResourceChanged OnResourceChanged;

	UFUNCTION(BlueprintCallable)
	void AddResource(EResourceType Type, float Amount);

	// returns false and consumes nothing if not enough
	UFUNCTION(BlueprintCallable)
	bool ConsumeResource(EResourceType Type, float Amount);

	UFUNCTION(BlueprintPure)
	float GetResource(EResourceType Type) const;

	UFUNCTION(BlueprintPure)
	bool HasResource(EResourceType Type, float Amount) const;

	// ===================== ENERGY =====================

	UPROPERTY(BlueprintAssignable)
	FOnEnergyChanged OnEnergyChanged;

	UPROPERTY(BlueprintReadOnly)
	float TotalEnergyProduction = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float TotalEnergyConsumption = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bBlackout = false;

	UFUNCTION(BlueprintCallable)
	void AddEnergyProduction(float Amount);

	UFUNCTION(BlueprintCallable)
	void RemoveEnergyProduction(float Amount);

	UFUNCTION(BlueprintCallable)
	void AddEnergyConsumption(float Amount);

	UFUNCTION(BlueprintCallable)
	void RemoveEnergyConsumption(float Amount);

	// ===================== DRONES =====================

	UPROPERTY(BlueprintAssignable)
	FOnDronesChanged OnDronesChanged;

	UPROPERTY(BlueprintReadOnly)
	int32 TotalDrones = 5;

	UPROPERTY(BlueprintReadOnly)
	int32 AssignedDrones = 0;

	UFUNCTION(BlueprintCallable)
	void AddDrones(int32 Count);

	// returns actual amount assigned (capped by idle count)
	UFUNCTION(BlueprintCallable)
	int32 AssignDrones(int32 Count);

	UFUNCTION(BlueprintCallable)
	void UnassignDrones(int32 Count);

	UFUNCTION(BlueprintPure)
	int32 GetIdleDrones() const { return TotalDrones - AssignedDrones; }

	// ===================== POPULATION =====================

	UPROPERTY(BlueprintAssignable)
	FOnPopulationChanged OnPopulationChanged;

	UPROPERTY(BlueprintReadOnly)
	int32 Population = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 HousingCapacity = 0;

	UFUNCTION(BlueprintCallable)
	void AddPopulation(int32 Count);

	UFUNCTION(BlueprintCallable)
	void AddHousingCapacity(int32 Count);

	UFUNCTION(BlueprintCallable)
	void RemoveHousingCapacity(int32 Count);

	// called each day — consumes biomasse/cadavre, applies happiness penalty if short
	void TickFood();

	// ===================== HAPPINESS =====================

	UPROPERTY(BlueprintAssignable)
	FOnHappinessChanged OnHappinessChanged;

	UPROPERTY(BlueprintReadOnly)
	float Comfort = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float Amusement = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float Satisfaction = 0.f;

	UFUNCTION(BlueprintCallable)
	void AddHappiness(EHappinessType Type, float Amount);

	UFUNCTION(BlueprintCallable)
	void RemoveHappiness(EHappinessType Type, float Amount);

	// 0-1, balanced average of C/A/S vs required happiness per pop
	UFUNCTION(BlueprintPure)
	float GetHappinessPercent() const;

	// ===================== TIME =====================

	UPROPERTY(BlueprintAssignable)
	FOnTimePassed OnTimePassed;

	UPROPERTY(BlueprintAssignable)
	FOnWeekPassed OnWeekPassed;

	// 1 day = 120 real seconds by default
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time")
	float DayDuration = 120.f;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentDay = 1;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentWeek = 1;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentMonth = 1;

	// 0 = paused, 1 = normal, 2/3/4 = fast
	UPROPERTY(BlueprintReadOnly)
	float TimeScale = 1.f;

	UFUNCTION(BlueprintCallable)
	void SetTimeScale(float NewScale);

	// ===================== REPUTATION =====================

	UPROPERTY(BlueprintAssignable)
	FOnReputationChanged OnReputationChanged;

	UPROPERTY(BlueprintReadOnly)
	float Reputation = 0.f;

	// rep tier table — populate in BP subclass
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reputation")
	TArray<FRepTierReward> RepTiers;

	UFUNCTION(BlueprintCallable)
	void ModifyReputation(float Delta);

	// returns the tier matching current reputation
	UFUNCTION(BlueprintPure)
	FRepTierReward GetCurrentRepTier() const;

	// ===================== MISSIONS =====================

	UPROPERTY(BlueprintAssignable)
	FOnMissionCompleted OnMissionCompleted;

	UPROPERTY(BlueprintReadOnly)
	TArray<FMissionData> ActiveMissions;

	// adds progress to all matching active missions
	UFUNCTION(BlueprintCallable)
	void UpdateMissionProgress(EMissionType Type, float Amount, EResourceType ResourceType = EResourceType::Acier);

	// called each week to replace completed missions with new ones
	void IssueNewMissions();

	// ===================== RESEARCH =====================

	UPROPERTY(BlueprintAssignable)
	FOnNodeUnlocked OnNodeUnlocked;

	UFUNCTION(BlueprintCallable)
	bool UnlockNode(UResearchNode* Node);

	UFUNCTION(BlueprintPure)
	bool IsUnlocked(FName Tag) const;

	// ===================== WAVES =====================

	UPROPERTY(BlueprintAssignable)
	FOnWaveStarted OnWaveStarted;

	UPROPERTY(BlueprintReadOnly)
	int32 WaveNumber = 0;

	// aliens killed this wave — tracks KillAliens missions
	UPROPERTY(BlueprintReadOnly)
	int32 AliensKilledTotal = 0;

	UFUNCTION(BlueprintCallable)
	void RegisterAlienKill();

	// class to spawn — set in BP subclass
	UPROPERTY(EditAnywhere, Category = "Waves")
	TSubclassOf<ANativeHorde> HordeClass;

private:
	UPROPERTY()
	TArray<FGridTile> Grid;

	UPROPERTY()
	TMap<EResourceType, float> Resources;

	UPROPERTY()
	TSet<FName> UnlockedResearch;

	FTimerHandle DayTimerHandle;
	FTimerHandle WaveTimerHandle;

	int32 CurrentDomeSize = 13; // Mark I default

	void OnDayTick();
	void OnWeekTick();
	void SpawnNextWave();

	int32 CalculateWaveSize() const;
	void CheckBlackout();
	void ApplyWeeklyHappinessPenalties();
	void ApplyWeeklyReputationRewards();

	// returns tile index in flat array
	int32 TileIndex(FIntPoint Coords) const { return Coords.X + Coords.Y * GridWidth; }
};

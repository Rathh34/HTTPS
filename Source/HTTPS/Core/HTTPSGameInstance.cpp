#include "HTTPSGameInstance.h"
#include "ResearchNode.h"
#include "NativeHorde.h"
#include "TimerManager.h"
#include "Engine/World.h"

UHTTPSGameInstance::UHTTPSGameInstance()
{
	// pre-populate resources so GetResource never returns a missing key
	for (uint8 i = 0; i <= (uint8)EResourceType::CadavreAlien; i++)
		Resources.Add((EResourceType)i, 0.f);
}

void UHTTPSGameInstance::Init()
{
	Super::Init();
	InitGrid();
}

void UHTTPSGameInstance::Shutdown()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(DayTimerHandle);
		World->GetTimerManager().ClearTimer(WaveTimerHandle);
	}
	Super::Shutdown();
}

void UHTTPSGameInstance::StartGame()
{
	UWorld* World = GetWorld();
	if (!World) return;

	// dome starts as Mark I (13x13)
	SetDomeSize(13);

	// day timer — scaled by TimeScale via SetTimer loop
	const float ActualDayDuration = DayDuration / FMath::Max(TimeScale, 0.01f);
	World->GetTimerManager().SetTimer(DayTimerHandle, this, &UHTTPSGameInstance::OnDayTick, ActualDayDuration, true);

	// wave timer — 150s ± 30s
	const float WaveDelay = FMath::FRandRange(120.f, 180.f);
	World->GetTimerManager().SetTimer(WaveTimerHandle, this, &UHTTPSGameInstance::SpawnNextWave, WaveDelay, false);

	IssueNewMissions();
}

// ===================== GRID =====================

void UHTTPSGameInstance::InitGrid()
{
	Grid.SetNum(GridWidth * GridHeight);
	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			FGridTile& Tile = Grid[TileIndex(FIntPoint(x, y))];
			Tile.Coords     = FIntPoint(x, y);
			Tile.State      = ETileState::DomeExterior;
		}
	}
}

FGridTile UHTTPSGameInstance::GetTile(FIntPoint Coords) const
{
	if (!IsTileValid(Coords)) return FGridTile();
	return Grid[TileIndex(Coords)];
}

void UHTTPSGameInstance::SetTileState(FIntPoint Coords, ETileState NewState)
{
	if (!IsTileValid(Coords)) return;
	Grid[TileIndex(Coords)].State = NewState;
}

bool UHTTPSGameInstance::IsTileValid(FIntPoint Coords) const
{
	return Coords.X >= 0 && Coords.Y >= 0 && Coords.X < GridWidth && Coords.Y < GridHeight;
}

bool UHTTPSGameInstance::CanPlaceBuilding(FIntPoint Origin, FIntPoint Footprint, ETileZone Zone) const
{
	for (int32 y = 0; y < Footprint.Y; y++)
	{
		for (int32 x = 0; x < Footprint.X; x++)
		{
			FIntPoint TileCoords = Origin + FIntPoint(x, y);
			if (!IsTileValid(TileCoords)) return false;

			const FGridTile& Tile = Grid[TileIndex(TileCoords)];
			if (Tile.Occupant != nullptr) return false;

			// zone check
			if (Zone == ETileZone::Interior && Tile.State != ETileState::DomeInterior) return false;
			if (Zone == ETileZone::Exterior && Tile.State != ETileState::DomeExterior)  return false;
			// ETileZone::Both accepts interior or exterior
			if (Zone == ETileZone::Both &&
				Tile.State != ETileState::DomeInterior &&
				Tile.State != ETileState::DomeExterior) return false;
		}
	}
	return true;
}

void UHTTPSGameInstance::OccupyTiles(FIntPoint Origin, FIntPoint Footprint, ABuildingBase* Building)
{
	for (int32 y = 0; y < Footprint.Y; y++)
	{
		for (int32 x = 0; x < Footprint.X; x++)
		{
			FIntPoint TileCoords = Origin + FIntPoint(x, y);
			if (!IsTileValid(TileCoords)) continue;

			FGridTile& Tile  = Grid[TileIndex(TileCoords)];
			Tile.Occupant    = Building;
			Tile.OriginCoords = Origin;
			Tile.State       = ETileState::Occupied;
		}
	}
}

void UHTTPSGameInstance::FreeTiles(FIntPoint Origin, FIntPoint Footprint)
{
	for (int32 y = 0; y < Footprint.Y; y++)
	{
		for (int32 x = 0; x < Footprint.X; x++)
		{
			FIntPoint TileCoords = Origin + FIntPoint(x, y);
			if (!IsTileValid(TileCoords)) continue;

			FGridTile& Tile = Grid[TileIndex(TileCoords)];
			Tile.Occupant   = nullptr;

			// restore state based on whether its inside or outside the dome
			const FIntPoint Center(GridWidth / 2, GridHeight / 2);
			const int32 HalfDome = CurrentDomeSize / 2;
			const bool bInside =
				FMath::Abs(TileCoords.X - Center.X) <= HalfDome &&
				FMath::Abs(TileCoords.Y - Center.Y) <= HalfDome;
			Tile.State = bInside ? ETileState::DomeInterior : ETileState::DomeExterior;
		}
	}
}

void UHTTPSGameInstance::SetDomeSize(int32 InteriorSize)
{
	CurrentDomeSize = InteriorSize;
	const FIntPoint Center(GridWidth / 2, GridHeight / 2);
	const int32 HalfDome = InteriorSize / 2;
	const int32 WallSize = 1; // 1 tile dome wall ring

	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			FGridTile& Tile = Grid[TileIndex(FIntPoint(x, y))];
			if (Tile.State == ETileState::Occupied) continue; // dont touch occupied tiles

			const int32 DX = FMath::Abs(x - Center.X);
			const int32 DY = FMath::Abs(y - Center.Y);

			if (DX <= HalfDome && DY <= HalfDome)
				Tile.State = ETileState::DomeInterior;
			else if (DX <= HalfDome + WallSize && DY <= HalfDome + WallSize)
				Tile.State = ETileState::DomeWall;
			else
				Tile.State = ETileState::DomeExterior;
		}
	}
}

FVector UHTTPSGameInstance::GridToWorld(FIntPoint Coords) const
{
	return FVector(Coords.X * TileSize, Coords.Y * TileSize, 0.f);
}

FIntPoint UHTTPSGameInstance::WorldToGrid(FVector WorldPos) const
{
	return FIntPoint(
		FMath::FloorToInt(WorldPos.X / TileSize),
		FMath::FloorToInt(WorldPos.Y / TileSize)
	);
}

// ===================== RESOURCES =====================

void UHTTPSGameInstance::AddResource(EResourceType Type, float Amount)
{
	if (Amount <= 0.f) return;
	Resources[Type] += Amount;
	OnResourceChanged.Broadcast(Type, Resources[Type]);
	UpdateMissionProgress(EMissionType::HarvestResource, Amount, Type);
}

bool UHTTPSGameInstance::ConsumeResource(EResourceType Type, float Amount)
{
	if (!HasResource(Type, Amount)) return false;
	Resources[Type] -= Amount;
	OnResourceChanged.Broadcast(Type, Resources[Type]);
	return true;
}

float UHTTPSGameInstance::GetResource(EResourceType Type) const
{
	const float* Found = Resources.Find(Type);
	return Found ? *Found : 0.f;
}

bool UHTTPSGameInstance::HasResource(EResourceType Type, float Amount) const
{
	return GetResource(Type) >= Amount;
}

// ===================== ENERGY =====================

void UHTTPSGameInstance::AddEnergyProduction(float Amount)
{
	TotalEnergyProduction += Amount;
	CheckBlackout();
}

void UHTTPSGameInstance::RemoveEnergyProduction(float Amount)
{
	TotalEnergyProduction = FMath::Max(0.f, TotalEnergyProduction - Amount);
	CheckBlackout();
}

void UHTTPSGameInstance::AddEnergyConsumption(float Amount)
{
	TotalEnergyConsumption += Amount;
	// each drone also consumes 1 energy — handled in AddDrones
	CheckBlackout();
}

void UHTTPSGameInstance::RemoveEnergyConsumption(float Amount)
{
	TotalEnergyConsumption = FMath::Max(0.f, TotalEnergyConsumption - Amount);
	CheckBlackout();
}

void UHTTPSGameInstance::CheckBlackout()
{
	const bool bNewBlackout = TotalEnergyConsumption > TotalEnergyProduction;
	if (bNewBlackout != bBlackout)
	{
		bBlackout = bNewBlackout;
		if (bBlackout)
		{
			UE_LOG(LogTemp, Warning, TEXT("[Energy] Blackout! Consumption %.0f > Production %.0f"), TotalEnergyConsumption, TotalEnergyProduction);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("[Energy] Power restored."));
		}
	}
	OnEnergyChanged.Broadcast(TotalEnergyProduction, TotalEnergyConsumption, bBlackout);
}

// ===================== DRONES =====================

void UHTTPSGameInstance::AddDrones(int32 Count)
{
	TotalDrones += Count;
	// each drone consumes 1 energy
	AddEnergyConsumption(Count);
	OnDronesChanged.Broadcast(TotalDrones, AssignedDrones);
}

int32 UHTTPSGameInstance::AssignDrones(int32 Count)
{
	const int32 Actual = FMath::Min(Count, GetIdleDrones());
	AssignedDrones += Actual;
	OnDronesChanged.Broadcast(TotalDrones, AssignedDrones);
	return Actual;
}

void UHTTPSGameInstance::UnassignDrones(int32 Count)
{
	AssignedDrones = FMath::Max(0, AssignedDrones - Count);
	OnDronesChanged.Broadcast(TotalDrones, AssignedDrones);
}

// ===================== POPULATION =====================

void UHTTPSGameInstance::AddPopulation(int32 Count)
{
	Population += Count;
	OnPopulationChanged.Broadcast(Population, HousingCapacity);
	UpdateMissionProgress(EMissionType::ReachPopulation, Count);
}

void UHTTPSGameInstance::AddHousingCapacity(int32 Count)
{
	HousingCapacity += Count;
	OnPopulationChanged.Broadcast(Population, HousingCapacity);
}

void UHTTPSGameInstance::RemoveHousingCapacity(int32 Count)
{
	HousingCapacity = FMath::Max(0, HousingCapacity - Count);
	OnPopulationChanged.Broadcast(Population, HousingCapacity);
}

void UHTTPSGameInstance::TickFood()
{
	if (Population <= 0) return;

	// 10 pop = 1 biomasse or cadavre alien per day
	const float FoodNeeded = Population / 10.f;
	float FoodAvailable = GetResource(EResourceType::Biomasse) + GetResource(EResourceType::CadavreAlien);

	if (FoodAvailable >= FoodNeeded)
	{
		// consume biomasse first, then cadavre
		float Remaining = FoodNeeded;
		const float BiomassUse = FMath::Min(Remaining, GetResource(EResourceType::Biomasse));
		ConsumeResource(EResourceType::Biomasse, BiomassUse);
		Remaining -= BiomassUse;
		if (Remaining > 0.f)
			ConsumeResource(EResourceType::CadavreAlien, Remaining);
	}
	else
	{
		// food shortage — happiness penalty
		RemoveHappiness(EHappinessType::Satisfaction, Population * 0.05f);
		UE_LOG(LogTemp, Warning, TEXT("[Food] Shortage — needed %.1f, had %.1f"), FoodNeeded, FoodAvailable);
	}
}

// ===================== HAPPINESS =====================

void UHTTPSGameInstance::AddHappiness(EHappinessType Type, float Amount)
{
	switch (Type)
	{
		case EHappinessType::Comfort:       Comfort       += Amount; break;
		case EHappinessType::Amusement:     Amusement     += Amount; break;
		case EHappinessType::Satisfaction:  Satisfaction  += Amount; break;
	}
	OnHappinessChanged.Broadcast(Comfort, Amusement, Satisfaction);
}

void UHTTPSGameInstance::RemoveHappiness(EHappinessType Type, float Amount)
{
	switch (Type)
	{
		case EHappinessType::Comfort:       Comfort       = FMath::Max(0.f, Comfort       - Amount); break;
		case EHappinessType::Amusement:     Amusement     = FMath::Max(0.f, Amusement     - Amount); break;
		case EHappinessType::Satisfaction:  Satisfaction  = FMath::Max(0.f, Satisfaction  - Amount); break;
	}
	OnHappinessChanged.Broadcast(Comfort, Amusement, Satisfaction);
}

float UHTTPSGameInstance::GetHappinessPercent() const
{
	if (Population <= 0) return 1.f;

	// each pop needs 1 happiness point — balanced across C/A/S
	const float Total = Comfort + Amusement + Satisfaction;
	return FMath::Clamp(Total / (Population * 3.f), 0.f, 1.f);
}

// ===================== TIME =====================

void UHTTPSGameInstance::SetTimeScale(float NewScale)
{
	TimeScale = FMath::Max(0.f, NewScale);

	UWorld* World = GetWorld();
	if (!World) return;

	if (TimeScale <= 0.f)
	{
		World->GetTimerManager().PauseTimer(DayTimerHandle);
	}
	else
	{
		World->GetTimerManager().UnPauseTimer(DayTimerHandle);
		const float ActualDayDuration = DayDuration / TimeScale;
		World->GetTimerManager().SetTimer(DayTimerHandle, this, &UHTTPSGameInstance::OnDayTick, ActualDayDuration, true);
	}
}

void UHTTPSGameInstance::OnDayTick()
{
	TickFood();

	// happiness < 60% → pop drops 5% per day
	if (GetHappinessPercent() < 0.6f && Population > 0)
	{
		const int32 PopLoss = FMath::CeilToInt(Population * 0.05f);
		Population = FMath::Max(0, Population - PopLoss);
		OnPopulationChanged.Broadcast(Population, HousingCapacity);
		UE_LOG(LogTemp, Warning, TEXT("[Happiness] Pop dropped %d (low happiness)"), PopLoss);
	}

	OnTimePassed.Broadcast(CurrentDay, CurrentWeek, CurrentMonth);
	CurrentDay++;

	// 7 days per week
	if (CurrentDay % 7 == 0)
		OnWeekTick();
}

void UHTTPSGameInstance::OnWeekTick()
{
	ApplyWeeklyHappinessPenalties();
	ApplyWeeklyReputationRewards();
	IssueNewMissions();

	// housing shortage → -15% happiness per week
	if (Population > HousingCapacity)
	{
		const float Penalty = Population * 0.15f;
		RemoveHappiness(EHappinessType::Comfort, Penalty / 3.f);
		RemoveHappiness(EHappinessType::Amusement, Penalty / 3.f);
		RemoveHappiness(EHappinessType::Satisfaction, Penalty / 3.f);
	}

	OnWeekPassed.Broadcast(CurrentWeek);
	CurrentWeek++;
	if (CurrentWeek % 4 == 0) CurrentMonth++;
}

// ===================== REPUTATION =====================

void UHTTPSGameInstance::ModifyReputation(float Delta)
{
	Reputation = FMath::Max(0.f, Reputation + Delta);
	OnReputationChanged.Broadcast(Reputation);
}

FRepTierReward UHTTPSGameInstance::GetCurrentRepTier() const
{
	FRepTierReward Best;
	for (const FRepTierReward& Tier : RepTiers)
		if (Reputation >= Tier.RepThreshold) Best = Tier;
	return Best;
}

void UHTTPSGameInstance::ApplyWeeklyHappinessPenalties()
{
	const float H = GetHappinessPercent();
	if (H < 0.8f)
	{
		ModifyReputation(-100.f);
		UE_LOG(LogTemp, Log, TEXT("[Rep] -100 rep (happiness below 80%%)"));
	}
	else if (H >= 1.f)
	{
		ModifyReputation(200.f);
		UE_LOG(LogTemp, Log, TEXT("[Rep] +200 rep (100%% happiness)"));
	}
}

void UHTTPSGameInstance::ApplyWeeklyReputationRewards()
{
	const FRepTierReward Tier = GetCurrentRepTier();

	if (Tier.OrReward > 0.f)
		AddResource(EResourceType::Or, Tier.OrReward);

	if (Tier.PopReward > 0)
		AddPopulation(Tier.PopReward);

	UE_LOG(LogTemp, Log, TEXT("[Rep] Weekly reward: %.0f or, %d pop"), Tier.OrReward, Tier.PopReward);
}

// ===================== MISSIONS =====================

void UHTTPSGameInstance::UpdateMissionProgress(EMissionType Type, float Amount, EResourceType ResourceType)
{
	for (FMissionData& Mission : ActiveMissions)
	{
		if (Mission.bCompleted || Mission.Type != Type) continue;
		if (Type == EMissionType::HarvestResource && Mission.ResourceType != ResourceType) continue;

		Mission.CurrentProgress += Amount;
		if (Mission.CurrentProgress >= Mission.TargetValue)
		{
			Mission.bCompleted = true;
			ModifyReputation(Mission.RepReward);
			OnMissionCompleted.Broadcast(Mission);
			UE_LOG(LogTemp, Log, TEXT("[Mission] Completed: %s (+%.0f rep)"), *Mission.Description.ToString(), Mission.RepReward);
		}
	}
}

void UHTTPSGameInstance::IssueNewMissions()
{
	// remove completed, add fresh ones — simple for now
	// TODO: make this data-driven from a mission pool asset
	ActiveMissions.RemoveAll([](const FMissionData& M) { return M.bCompleted; });

	while (ActiveMissions.Num() < 3)
	{
		FMissionData New;
		const int32 Roll = FMath::RandRange(0, 2);
		if (Roll == 0)
		{
			New.Type         = EMissionType::HarvestResource;
			New.ResourceType = EResourceType::Acier;
			New.TargetValue  = 500.f;
			New.RepReward    = 25.f;
			New.Description  = FText::FromString(TEXT("Récolter 500 Acier"));
		}
		else if (Roll == 1)
		{
			New.Type        = EMissionType::KillAliens;
			New.TargetValue = 20.f;
			New.RepReward   = 200.f;
			New.Description = FText::FromString(TEXT("Tuer 20 Aliens"));
		}
		else
		{
			New.Type        = EMissionType::ReachPopulation;
			New.TargetValue = Population + 100.f;
			New.RepReward   = 150.f;
			New.Description = FText::FromString(TEXT("Atteindre +100 habitants"));
		}
		ActiveMissions.Add(New);
	}
}

// ===================== RESEARCH =====================

bool UHTTPSGameInstance::UnlockNode(UResearchNode* Node)
{
	if (!Node) return false;
	if (IsUnlocked(Node->UnlockTag)) return false;

	// check prereqs
	for (const FName& Prereq : Node->Prerequisites)
		if (!IsUnlocked(Prereq)) return false;

	// pop threshold
	if (Population < Node->RequiredPopulation) return false;

	if (!ConsumeResource(EResourceType::Or, Node->GoldCost)) return false;

	UnlockedResearch.Add(Node->UnlockTag);
	OnNodeUnlocked.Broadcast(Node->UnlockTag);
	UE_LOG(LogTemp, Log, TEXT("[Research] Unlocked: %s"), *Node->UnlockTag.ToString());
	return true;
}

bool UHTTPSGameInstance::IsUnlocked(FName Tag) const
{
	if (Tag.IsNone()) return true; // empty tag = always available
	return UnlockedResearch.Contains(Tag);
}

// ===================== WAVES =====================

void UHTTPSGameInstance::RegisterAlienKill()
{
	AliensKilledTotal++;
	UpdateMissionProgress(EMissionType::KillAliens, 1.f);
}

void UHTTPSGameInstance::SpawnNextWave()
{
	WaveNumber++;
	const int32 WaveSize = CalculateWaveSize();

	if (HordeClass && GetWorld())
	{
		// spawn horde near dome center — level designer should place spawn markers
		// TODO: use designer-placed spawn points instead of hardcoded location
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ANativeHorde* Horde = GetWorld()->SpawnActor<ANativeHorde>(HordeClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
		if (Horde) Horde->SpawnHorde(WaveSize);
	}

	OnWaveStarted.Broadcast(WaveNumber, WaveSize);
	UE_LOG(LogTemp, Log, TEXT("[Wave] %d — %d aliens"), WaveNumber, WaveSize);

	// schedule next wave: 150s ± 30s
	const float NextWaveDelay = FMath::FRandRange(120.f, 180.f) / FMath::Max(TimeScale, 0.01f);
	GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &UHTTPSGameInstance::SpawnNextWave, NextWaveDelay, false);
}

int32 UHTTPSGameInstance::CalculateWaveSize() const
{
	// formula from GDD: 5+5*((x-1)/3)+5*((x-1)%3)
	const int32 x = WaveNumber;
	return 5 + 5 * ((x - 1) / 3) + 5 * ((x - 1) % 3);
}

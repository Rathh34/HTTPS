#include "HTTPSGameState.h"
#include "HTTPSGameInstance.h"

AHTTPSGameState::AHTTPSGameState()
{
}

void AHTTPSGameState::BeginPlay()
{
	Super::BeginPlay();
	BindToGameInstance();
}

void AHTTPSGameState::BindToGameInstance()
{
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;

	GI->OnPopulationChanged.AddDynamic(this, &AHTTPSGameState::OnPopulationChanged);
	GI->OnReputationChanged.AddDynamic(this, &AHTTPSGameState::OnReputationChanged);
	GI->OnTimePassed.AddDynamic(this,        &AHTTPSGameState::OnTimePassed);
}

void AHTTPSGameState::SetPhase(EGamePhase NewPhase)
{
	if (Phase == NewPhase) return;
	Phase = NewPhase;
	UE_LOG(LogTemp, Warning, TEXT("[GameState] Phase -> %d"), (uint8)NewPhase);
}

void AHTTPSGameState::OnPopulationChanged(int32 NewPop, int32 HousingCap)
{
	Population = NewPop;
}

void AHTTPSGameState::OnReputationChanged(float NewRep)
{
	Reputation = NewRep;
}

void AHTTPSGameState::OnTimePassed(int32 Day, int32 Week, int32 Month)
{
	CurrentDay   = Day;
	CurrentWeek  = Week;
	CurrentMonth = Month;
}

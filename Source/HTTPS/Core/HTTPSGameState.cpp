#include "HTTPSGameState.h"

AHTTPSGameState::AHTTPSGameState()
{
}

void AHTTPSGameState::AddPopulation(int32 Amount)
{
	Population += Amount;
	UE_LOG(LogTemp, Log, TEXT("[GameState] Population: %d"), Population);

	if (Population >= 5000000)
		SetPhase(EGamePhase::Win);
}

void AHTTPSGameState::ModifyReputation(float Delta)
{
	Reputation = FMath::Clamp(Reputation + Delta, 0.f, 100.f);
	UE_LOG(LogTemp, Log, TEXT("[GameState] Reputation: %.1f"), Reputation);
}

void AHTTPSGameState::AdvanceWeek()
{
	CurrentWeek++;
	UE_LOG(LogTemp, Log, TEXT("[GameState] Week %d"), CurrentWeek);
}

void AHTTPSGameState::SetPhase(EGamePhase NewPhase)
{
	if (CurrentPhase == NewPhase) return;
	CurrentPhase = NewPhase;
	UE_LOG(LogTemp, Warning, TEXT("[GameState] Phase -> %d"), (uint8)NewPhase);
}

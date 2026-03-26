#include "HTTPSGameState.h"

AHTTPSGameState::AHTTPSGameState()
{
}

void AHTTPSGameState::AddPopulation(int32 Amount)
{
	Population += Amount;
	if (Population >= 5000000)
		CurrentPhase = EGamePhase::Win;
}

void AHTTPSGameState::ModifyReputation(float Delta)
{
	Reputation = FMath::Clamp(Reputation + Delta, 0.f, 100.f);
}

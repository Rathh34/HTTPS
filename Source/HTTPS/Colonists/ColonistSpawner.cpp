#include "ColonistSpawner.h"
#include "Colonist.h"
#include "WorkforceManager.h"
#include "Core/HTTPSGameState.h"
#include "Engine/World.h"

AColonistSpawner::AColonistSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AColonistSpawner::OnWeekElapsed()
{
	if (!WorkforceManager || !ColonistClass) return;

	const int32 Count = CalculateArrivals();

	for (int32 i = 0; i < Count; i++)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AColonist* NewColonist = GetWorld()->SpawnActor<AColonist>(ColonistClass, GetActorLocation(), FRotator::ZeroRotator, Params);
		if (NewColonist)
			WorkforceManager->RegisterColonist(NewColonist);
	}

	if (AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>())
		GS->AddPopulation(Count);

	UE_LOG(LogTemp, Log, TEXT("[Week] %d colonists arrived."), Count);
}

int32 AColonistSpawner::CalculateArrivals() const
{
	// 0 rep = nobody, 50 = base, 100 = 2x
	AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>();
	const float Rep = GS ? GS->Reputation : 50.f;
	return FMath::Max(0, FMath::RoundToInt(BaseWeeklyArrivals * (Rep / 50.f)));
}

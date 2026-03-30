#include "ColonistSpawner.h"
#include "Colonist.h"
#include "WorkforceManager.h"
#include "HTTPS/Core/HTTPSGameState.h"
#include "Engine/World.h"
#include "TimerManager.h"

AColonistSpawner::AColonistSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AColonistSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		WeekTimerHandle,
		this,
		&AColonistSpawner::OnWeekElapsed,
		WeekDuration,
		true // loop
	);
}

void AColonistSpawner::OnWeekElapsed()
{
	if (!WorkforceManager || !ColonistClass) return;

	const int32 Count = CalculateArrivals();

	for (int32 i = 0; i < Count; i++)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AColonist* NewColonist = GetWorld()->SpawnActor<AColonist>(
			ColonistClass, GetActorLocation(), FRotator::ZeroRotator, Params
		);

		if (NewColonist)
			WorkforceManager->RegisterColonist(NewColonist);
	}

	if (AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>())
	{
		GS->AddPopulation(Count);
		GS->AdvanceWeek();
	}

	UE_LOG(LogTemp, Log, TEXT("Week elapsed: %d colonists arrived."), Count);
}

int32 AColonistSpawner::CalculateArrivals() const
{
	// 0 rep = nobody comes, 50 rep = base amount, 100 rep = 2x base
	AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>();
	const float Rep = GS ? GS->Reputation : 50.f;
	const float Scale = Rep / 50.f;
	return FMath::Max(0, FMath::RoundToInt(BaseWeeklyArrivals * Scale));
}
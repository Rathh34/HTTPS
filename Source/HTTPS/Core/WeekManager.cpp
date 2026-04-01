#include "WeekManager.h"
#include "HTTPSGameState.h"
#include "Colonists/ColonistSpawner.h"
#include "Reputation/ReputationManager.h"
#include "TimerManager.h"

AWeekManager::AWeekManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeekManager::BeginPlay()
{
	Super::BeginPlay();

	if (AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>())
		GS->SetPhase(EGamePhase::Playing);

	GetWorldTimerManager().SetTimer(
		WeekTimerHandle,
		this,
		&AWeekManager::OnWeekElapsed,
		WeekDuration,
		true
	);
}

void AWeekManager::OnWeekElapsed()
{
	AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>();
	if (!GS) return;

	if (GS->CurrentPhase == EGamePhase::Win || GS->CurrentPhase == EGamePhase::Lose)
	{
		GetWorldTimerManager().ClearTimer(WeekTimerHandle);
		return;
	}

	GS->AdvanceWeek();

	if (ColonistSpawner)
		ColonistSpawner->OnWeekElapsed();

	if (ReputationManager)
		ReputationManager->OnWeekPassed();

	OnWeekPassed.Broadcast(GS->CurrentWeek);
}
#include "ReputationManager.h"
#include "HTTPS/Core/HTTPSGameState.h"
#include "HTTPS/Resources/ResourceManager.h"

AReputationManager::AReputationManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AReputationManager::BeginPlay()
{
	Super::BeginPlay();
	IssueNewObjective();
}

void AReputationManager::OnWeekPassed()
{
	AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>();
	if (!GS || CurrentObjective.bCompleted || CurrentObjective.bFailed) return;

	const int32 WeeksElapsed = GS->CurrentWeek - WeekIssuedOn;
	if (WeeksElapsed < CurrentObjective.WeekDeadline) return;

	if (EvaluateObjective())
	{
		CurrentObjective.bCompleted = true;
		GS->ModifyReputation(CurrentObjective.ReputationReward);
		OnObjectiveCompleted.Broadcast(CurrentObjective);
		UE_LOG(LogTemp, Log, TEXT("[Reputation] Objective completed. Rep: %.1f"), GS->Reputation);
	}
	else
	{
		CurrentObjective.bFailed = true;
		GS->ModifyReputation(CurrentObjective.ReputationPenalty);
		OnObjectiveFailed.Broadcast(CurrentObjective);
		UE_LOG(LogTemp, Log, TEXT("[Reputation] Objective failed. Rep: %.1f"), GS->Reputation);
	}

	IssueNewObjective();
}

bool AReputationManager::EvaluateObjective() const
{
	AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>();
	if (!GS) return false;

	switch (CurrentObjective.Type)
	{
		case EObjectiveType::ReachPopulation:
			return GS->Population >= (int32)CurrentObjective.TargetValue;

		case EObjectiveType::ProduceResource:
			return ResourceManager &&
				ResourceManager->GetResource(CurrentObjective.ResourceType) >= CurrentObjective.TargetValue;

		case EObjectiveType::MaintainReputation:
			return GS->Reputation >= CurrentObjective.TargetValue;
	}
	return false;
}

void AReputationManager::IssueNewObjective()
{
	AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>();
	if (!GS) return;

	WeekIssuedOn = GS->CurrentWeek;
	CurrentObjective = FGovernmentObjective();

	const int32 Roll = FMath::RandRange(0, 2);
	if (Roll == 0)
	{
		CurrentObjective.Type = EObjectiveType::ReachPopulation;
		CurrentObjective.TargetValue = GS->Population + 50.f;
		CurrentObjective.Description = FText::FromString(TEXT("Grow population by 50"));
	}
	else if (Roll == 1)
	{
		CurrentObjective.Type = EObjectiveType::ProduceResource;
		CurrentObjective.ResourceType = EResourceType::Metal;
		CurrentObjective.TargetValue = 500.f;
		CurrentObjective.Description = FText::FromString(TEXT("Stockpile 500 Metal"));
	}
	else
	{
		CurrentObjective.Type = EObjectiveType::MaintainReputation;
		CurrentObjective.TargetValue = 40.f;
		CurrentObjective.Description = FText::FromString(TEXT("Keep reputation above 40"));
	}

	UE_LOG(LogTemp, Log, TEXT("[Reputation] New objective: %s"), *CurrentObjective.Description.ToString());
}
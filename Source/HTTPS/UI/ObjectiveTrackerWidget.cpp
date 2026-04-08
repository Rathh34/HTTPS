#include "ObjectiveTrackerWidget.h"
#include "Reputation/ReputationManager.h"
#include "Core/HTTPSGameState.h"

void UObjectiveTrackerWidget::RefreshObjective()
{
	if (!ReputationManager) return;

	AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>();
	if (!GS) return;

	const FGovernmentObjective& Obj = ReputationManager->GetCurrentObjective();
	const int32 WeeksRemaining = FMath::Max(0, Obj.WeekDeadline - (GS->CurrentWeek - 0));

	OnObjectiveRefreshed(Obj.Description, WeeksRemaining, GS->Reputation);
}

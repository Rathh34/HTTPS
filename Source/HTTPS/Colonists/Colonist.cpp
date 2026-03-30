#include "Colonist.h"

AColonist::AColonist()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AColonist::AssignTo(AActor* Workplace)
{
	if (!Workplace) return;
	AssignedWorkplace = Workplace;
	State = EColonistState::Assigned;
}

void AColonist::Unassign()
{
	AssignedWorkplace = nullptr;
	State = EColonistState::Idle;
}
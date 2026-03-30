#include "WorkforceManager.h"
#include "Colonist.h"

AWorkforceManager::AWorkforceManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWorkforceManager::RegisterColonist(AColonist* Colonist)
{
	if (!Colonist) return;
	AllColonists.AddUnique(Colonist);
	OnWorkforceChanged.Broadcast(GetIdleCount());
}

bool AWorkforceManager::AssignColonistTo(AActor* Workplace)
{
	AColonist* Idle = FindIdleColonist();
	if (!Idle) return false;

	Idle->AssignTo(Workplace);
	OnWorkforceChanged.Broadcast(GetIdleCount());
	return true;
}

void AWorkforceManager::UnassignFromWorkplace(AActor* Workplace)
{
	for (AColonist* C : AllColonists)
	{
		if (C && C->AssignedWorkplace == Workplace)
		{
			C->Unassign();
		}
	}
	OnWorkforceChanged.Broadcast(GetIdleCount());
}

int32 AWorkforceManager::GetIdleCount() const
{
	int32 Count = 0;
	for (const AColonist* C : AllColonists)
	{
		if (C && C->IsIdle()) Count++;
	}
	return Count;
}

AColonist* AWorkforceManager::FindIdleColonist() const
{
	for (AColonist* C : AllColonists)
	{
		if (C && C->IsIdle()) return C;
	}
	return nullptr;
}

TArray<AColonist*> AWorkforceManager::GetAllColonists() const
{
	TArray<AColonist*> Result;
	for (const TObjectPtr<AColonist>& C : AllColonists)
	{
		if (C) Result.Add(C.Get());
	}
	return Result;
}
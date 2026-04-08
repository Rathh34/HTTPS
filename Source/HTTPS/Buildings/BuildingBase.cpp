#include "BuildingBase.h"
#include "Colonists/Colonist.h"

ABuildingBase::ABuildingBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	SetState(EBuildingState::Operational); // skipping constructing phase for now
}

void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOperational() && AssignedWorkers.Num() > 0)
		OnOperationalTick(DeltaTime);
}

bool ABuildingBase::AssignWorker(AColonist* Colonist)
{
	if (!Colonist || AssignedWorkers.Num() >= MaxWorkers) return false;
	AssignedWorkers.AddUnique(Colonist);
	Colonist->AssignTo(this);
	OnWorkerChanged.Broadcast(Colonist, true);
	return true;
}

void ABuildingBase::RemoveWorker(AColonist* Colonist)
{
	if (!Colonist) return;
	AssignedWorkers.Remove(Colonist);
	Colonist->Unassign();
	OnWorkerChanged.Broadcast(Colonist, false);
}

void ABuildingBase::ApplyDamage_Implementation(float Amount, AActor* DamageSource)
{
	if (State == EBuildingState::Destroyed) return;

	CurrentHealth = FMath::Max(0.f, CurrentHealth - Amount);

	if (CurrentHealth <= 0.f)
	{
		SetState(EBuildingState::Destroyed);
		// kick everyone out before the building goes down
		for (AColonist* C : AssignedWorkers)
			if (C) C->Unassign();
		AssignedWorkers.Empty();
	}
	else if (CurrentHealth < MaxHealth * 0.5f)
	{
		SetState(EBuildingState::Damaged);
	}
}

void ABuildingBase::SetState(EBuildingState NewState)
{
	if (State == NewState) return;
	State = NewState;
	OnStateChanged.Broadcast(NewState);
}

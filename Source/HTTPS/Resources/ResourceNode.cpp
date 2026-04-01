#include "ResourceNode.h"
#include "HTTPS/Colonists/Colonist.h"

AResourceNode::AResourceNode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResourceNode::BeginPlay()
{
	Super::BeginPlay();
	CurrentReserve = MaxReserve;
}

void AResourceNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AssignedWorkers.IsEmpty() || CurrentReserve <= 0.f || !ResourceManager) return;

	const float Amount = FMath::Min(
		YieldPerWorkerPerSecond * AssignedWorkers.Num() * DeltaTime,
		CurrentReserve
	);

	CurrentReserve -= Amount;
	ResourceManager->AddResource(ResourceType, Amount);
}

bool AResourceNode::AssignWorker(AColonist* Colonist)
{
	if (!Colonist || AssignedWorkers.Num() >= MaxWorkers) return false;
	AssignedWorkers.AddUnique(Colonist);
	Colonist->AssignTo(this);
	return true;
}

void AResourceNode::RemoveWorker(AColonist* Colonist)
{
	AssignedWorkers.Remove(Colonist);
	if (Colonist) Colonist->Unassign();
}
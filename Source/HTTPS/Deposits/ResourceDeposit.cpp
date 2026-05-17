#include "ResourceDeposit.h"
#include "HTTPSGameInstance.h"

AResourceDeposit::AResourceDeposit()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResourceDeposit::BeginPlay()
{
	Super::BeginPlay();
	CurrentReserve = MaxReserve;

	// register tile as ResourceDeposit so placement system blocks it
	if (UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>())
	{
		FIntPoint GridPos = GI->WorldToGrid(GetActorLocation());
		if (GI->IsTileValid(GridPos))
			GI->SetTileState(GridPos, ETileState::ResourceDeposit);
	}
}

void AResourceDeposit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AssignedDrones <= 0) return;
	if (!bInfiniteReserve && CurrentReserve <= 0.f) return;

	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI || GI->bBlackout) return;

	const float Amount = BaseYieldPerDronePerSecond * AssignedDrones * DeltaTime;

	if (!bInfiniteReserve)
	{
		const float Actual = FMath::Min(Amount, CurrentReserve);
		CurrentReserve -= Actual;
		GI->AddResource(ResourceType, Actual);
	}
	else
	{
		// synthétiseur unlocked — deposit never depletes
		GI->AddResource(ResourceType, Amount);
	}
}

int32 AResourceDeposit::AssignDrones(int32 Count)
{
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return 0;

	const int32 CanTake = FMath::Min(Count, MaxDrones - AssignedDrones);
	const int32 Actual  = GI->AssignDrones(CanTake);
	AssignedDrones += Actual;
	return Actual;
}

void AResourceDeposit::UnassignDrones(int32 Count)
{
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;

	const int32 Actual = FMath::Min(Count, AssignedDrones);
	GI->UnassignDrones(Actual);
	AssignedDrones -= Actual;
}

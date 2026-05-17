#include "BuildingBase.h"
#include "HealthComponent.h"
#include "DroneComponent.h"
#include "EnergyComponent.h"
#include "HTTPSGameInstance.h"

ABuildingBase::ABuildingBase()
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	DroneComp  = CreateDefaultSubobject<UDroneComponent>(TEXT("DroneComp"));
	EnergyComp = CreateDefaultSubobject<UEnergyComponent>(TEXT("EnergyComp"));
}

void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();

	HealthComp->OnDied.AddDynamic(this, &ABuildingBase::OnDied);

	// apply data asset values to components
	if (BuildingData)
	{
		HealthComp->MaxHealth     = BuildingData->MaxHealth;
		DroneComp->MaxDrones      = BuildingData->MaxDrones;
		EnergyComp->EnergyDelta   = BuildingData->EnergyDelta;
	}
}

void ABuildingBase::EndPlay(const EEndPlayReason::Type Reason)
{
	// free grid tiles on destroy
	if (UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>())
		GI->FreeTiles(GridOrigin, GridFootprint);

	// housing capacity cleanup handled by subclasses
	Super::EndPlay(Reason);
}

void ABuildingBase::OnPlaced(FIntPoint Origin, bool bInRotated)
{
	GridOrigin = Origin;
	bRotated   = bInRotated;

	if (BuildingData)
	{
		GridFootprint = bRotated ?
			FIntPoint(BuildingData->FootprintSize.Y, BuildingData->FootprintSize.X) :
			BuildingData->FootprintSize;
	}

	if (UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>())
		GI->OccupyTiles(GridOrigin, GridFootprint, this);

	// construction skipped for now — go straight to operational
	// TODO: add construction timer using BuildingData->BuildTime
	SetOperational();
}

void ABuildingBase::SetOperational()
{
	SetState(EBuildingState::Operational);
	OnOperational();
}

void ABuildingBase::SetState(EBuildingState NewState)
{
	if (State == NewState) return;
	State = NewState;
	OnStateChanged.Broadcast(NewState);
}

void ABuildingBase::OnDied()
{
	SetState(EBuildingState::Destroyed);
	DroneComp->UnassignAll();
	UE_LOG(LogTemp, Log, TEXT("[Building] %s destroyed"), *GetNameSafe(this));
	Destroy();
}

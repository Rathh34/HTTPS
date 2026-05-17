#include "DroneFactory.h"
#include "DroneComponent.h"
#include "HTTPSGameInstance.h"
#include "TimerManager.h"

ADroneFactory::ADroneFactory()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADroneFactory::OnOperational()
{
	// scale interval by drone efficiency — fewer drones = slower production
	const float Efficiency = FMath::Max(DroneComp->GetEfficiency(), 0.01f);
	const float Interval   = ProductionInterval / Efficiency;

	GetWorldTimerManager().SetTimer(ProductionTimer, this, &ADroneFactory::ProduceDrone, Interval, true);
}

void ADroneFactory::EndPlay(const EEndPlayReason::Type Reason)
{
	GetWorldTimerManager().ClearTimer(ProductionTimer);
	Super::EndPlay(Reason);
}

void ADroneFactory::ProduceDrone()
{
	if (!IsOperational()) return;

	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;

	// @note: factory only runs if energy is not cut — blackout check in GameInstance
	if (GI->bBlackout) return;

	GI->AddDrones(1);
	UE_LOG(LogTemp, Log, TEXT("[DroneFactory] Produced 1 drone (total: %d)"), GI->TotalDrones);
}

#include "EnergyComponent.h"
#include "HTTPSGameInstance.h"
#include "Engine/World.h"

UEnergyComponent::UEnergyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnergyComponent::BeginPlay()
{
	Super::BeginPlay();
	if (EnergyDelta != 0.f)
		RegisterWithGameInstance(true);
}

void UEnergyComponent::EndPlay(const EEndPlayReason::Type Reason)
{
	if (bActive && EnergyDelta != 0.f)
		RegisterWithGameInstance(false);
	Super::EndPlay(Reason);
}

void UEnergyComponent::SetEnergyActive(bool bNewActive)
{
	if (bActive == bNewActive) return;
	bActive = bNewActive;
	RegisterWithGameInstance(bNewActive);
}

void UEnergyComponent::RegisterWithGameInstance(bool bRegister)
{
	UHTTPSGameInstance* GI = GetWorld() ? GetWorld()->GetGameInstance<UHTTPSGameInstance>() : nullptr;
	if (!GI || EnergyDelta == 0.f) return;

	if (EnergyDelta > 0.f)
	{
		if (bRegister) GI->AddEnergyProduction(EnergyDelta);
		else           GI->RemoveEnergyProduction(EnergyDelta);
	}
	else
	{
		// consumption is always a positive number
		if (bRegister) GI->AddEnergyConsumption(FMath::Abs(EnergyDelta));
		else           GI->RemoveEnergyConsumption(FMath::Abs(EnergyDelta));
	}
}

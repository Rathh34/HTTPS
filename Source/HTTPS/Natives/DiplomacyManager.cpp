#include "DiplomacyManager.h"
#include "NativeBase.h"
#include "Resources/ResourceManager.h"
#include "Resources/ResourceType.h"
#include "Kismet/GameplayStatics.h"

ADiplomacyManager::ADiplomacyManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool ADiplomacyManager::OfferTrade(float MetalCost)
{
	if (bExterminated || !ResourceManager) return false;
	if (!ResourceManager->ConsumeResource(EResourceType::Metal, MetalCost)) return false;

	ModifyHostility(-(MetalCost * 0.1f));
	return true;
}

void ADiplomacyManager::Exterminate()
{
	if (bExterminated) return;

	TArray<AActor*> Natives;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANativeBase::StaticClass(), Natives);
	for (AActor* A : Natives) A->Destroy();

	bExterminated = true;
	Hostility     = 0.f;
	OnStanceChanged.Broadcast(CurrentStance);
}

void ADiplomacyManager::ModifyHostility(float Delta)
{
	Hostility = FMath::Clamp(Hostility + Delta, 0.f, 100.f);
	UpdateStance();
}

void ADiplomacyManager::UpdateStance()
{
	EDiplomacyStance NewStance;

	if      (Hostility >= 60.f) NewStance = EDiplomacyStance::Hostile;
	else if (Hostility >= 25.f) NewStance = EDiplomacyStance::Neutral;
	else                        NewStance = EDiplomacyStance::Trading;

	if (NewStance != CurrentStance)
	{
		CurrentStance = NewStance;
		OnStanceChanged.Broadcast(CurrentStance);
	}
}

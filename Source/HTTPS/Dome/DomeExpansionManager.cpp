#include "DomeExpansionManager.h"
#include "DomeComponent.h"
#include "HTTPS/Resources/ResourceManager.h"
#include "HTTPS/Resources/ResourceType.h"

ADomeExpansionManager::ADomeExpansionManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool ADomeExpansionManager::TryExpand()
{
	if (!Dome || !ResourceManager) return false;

	if (!ResourceManager->ConsumeResource(EResourceType::RareMineral, ExpansionCost))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Dome] Not enough RareMineral to expand."));
		return false;
	}

	Dome->SetDomeRadius(Dome->GetDomeRadius() + ExpansionRadiusIncrease);
	UE_LOG(LogTemp, Log, TEXT("[Dome] Expanded to radius %.0f"), Dome->GetDomeRadius());
	return true;
}

float ADomeExpansionManager::GetCurrentRadius() const
{
	return Dome ? Dome->GetDomeRadius() : 0.f;
}
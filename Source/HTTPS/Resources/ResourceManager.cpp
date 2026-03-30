#include "ResourceManager.h"

AResourceManager::AResourceManager()
{
	PrimaryActorTick.bCanEverTick = false;

	// pre-populate so we never get a missing key on Get
	for (uint8 i = 0; i <= (uint8)EResourceType::ResearchPoints; i++)
		Resources.Add((EResourceType)i, 0.f);
}

void AResourceManager::AddResource(EResourceType Type, float Amount)
{
	if (Amount <= 0.f) return;
	Resources[Type] += Amount;
	OnResourceChanged.Broadcast(Type, Resources[Type]);
}

bool AResourceManager::ConsumeResource(EResourceType Type, float Amount)
{
	if (!HasResource(Type, Amount)) return false;
	Resources[Type] -= Amount;
	OnResourceChanged.Broadcast(Type, Resources[Type]);
	return true;
}

float AResourceManager::GetResource(EResourceType Type) const
{
	const float* Found = Resources.Find(Type);
	return Found ? *Found : 0.f;
}

bool AResourceManager::HasResource(EResourceType Type, float Amount) const
{
	return GetResource(Type) >= Amount;
}
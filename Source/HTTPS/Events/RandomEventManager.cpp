#include "RandomEventManager.h"
#include "EventBase.h"

ARandomEventManager::ARandomEventManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARandomEventManager::OnWeekPassed()
{
	if (EventPool.IsEmpty() || FMath::FRand() > EventChancePerWeek) return;

	UEventBase* Event = PickEvent();
	if (!Event) return;

	Event->Apply(this);
	OnEventTriggered.Broadcast(Event);
	UE_LOG(LogTemp, Log, TEXT("[Event] Triggered: %s"), *Event->EventName.ToString());
}

UEventBase* ARandomEventManager::PickEvent() const
{
	// weighted random — sum all weights, roll, walk the list
	float TotalWeight = 0.f;
	for (const TSubclassOf<UEventBase>& EC : EventPool)
		if (EC) TotalWeight += EC->GetDefaultObject<UEventBase>()->Weight;

	if (TotalWeight <= 0.f) return nullptr;

	float Roll = FMath::FRand() * TotalWeight;
	for (const TSubclassOf<UEventBase>& EC : EventPool)
	{
		if (!EC) continue;
		UEventBase* CDO = EC->GetDefaultObject<UEventBase>();
		Roll -= CDO->Weight;
		if (Roll <= 0.f)
			return NewObject<UEventBase>(const_cast<ARandomEventManager*>(this), EC);
	}

	return nullptr;
}

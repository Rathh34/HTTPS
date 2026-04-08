#include "MainHUDWidget.h"
#include "Core/HTTPSGameState.h"
#include "Resources/ResourceManager.h"
#include "Resources/ResourceType.h"
#include "Events/EventBase.h"
#include "EventNotificationWidget.h"
#include "ObjectiveTrackerWidget.h"

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TimeSinceRefresh += InDeltaTime;
	if (TimeSinceRefresh < RefreshInterval) return;
	TimeSinceRefresh = 0.f;

	if (ResourceManager)
	{
		RefreshResourceDisplay(
			ResourceManager->GetResource(EResourceType::Metal),
			ResourceManager->GetResource(EResourceType::Power),
			ResourceManager->GetResource(EResourceType::Food),
			ResourceManager->GetResource(EResourceType::Oxygen),
			ResourceManager->GetResource(EResourceType::RareMineral)
		);
	}

	if (AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>())
		RefreshPopulationDisplay(GS->Population, GS->Reputation);
}

void UMainHUDWidget::OnWeekPassed(int32 WeekNumber)
{
	if (ObjectiveTracker)
		ObjectiveTracker->RefreshObjective();
}

void UMainHUDWidget::ShowEventNotification(UEventBase* Event)
{
	if (EventNotification && Event)
		EventNotification->ShowEvent(Event->EventName, Event->EventDescription);
}

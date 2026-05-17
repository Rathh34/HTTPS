#include "EventNotificationWidget.h"
#include "TimerManager.h"

void UEventNotificationWidget::ShowEvent(const FText& Title, const FText& Message)
{
	SetVisibility(ESlateVisibility::Visible);
	OnEventShown(Title, Message);

	GetWorld()->GetTimerManager().SetTimer(HideTimer, this, &UEventNotificationWidget::Hide, DisplayDuration, false);
}

void UEventNotificationWidget::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

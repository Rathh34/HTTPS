#include "EventNotificationWidget.h"
#include "TimerManager.h"

void UEventNotificationWidget::ShowEvent(const FText& Name, const FText& Description)
{
	SetVisibility(ESlateVisibility::Visible);
	OnEventShown(Name, Description);

	GetWorld()->GetTimerManager().SetTimer(
		HideTimerHandle,
		this,
		&UEventNotificationWidget::HideNotification,
		DisplayDuration,
		false
	);
}

void UEventNotificationWidget::HideNotification()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

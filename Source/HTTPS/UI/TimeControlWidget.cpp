#include "TimeControlWidget.h"
#include "HTTPSGameInstance.h"

void UTimeControlWidget::SetTimeScale(float Scale)
{
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (GI) GI->SetTimeScale(Scale);
}

void UTimeControlWidget::Pause()
{
	SetTimeScale(0.f);
}

void UTimeControlWidget::Resume()
{
	// restore to x1 when unpausing
	SetTimeScale(1.f);
}

float UTimeControlWidget::GetCurrentTimeScale() const
{
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	return GI ? GI->TimeScale : 1.f;
}

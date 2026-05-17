#include "MissionWidget.h"
#include "HTTPSGameInstance.h"

void UMissionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;

	GI->OnMissionCompleted.AddDynamic(this, &UMissionWidget::OnMissionCompleted);
	RefreshMissions();
}

void UMissionWidget::RefreshMissions()
{
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;
	OnMissionsRefreshed(GI->ActiveMissions);
}

void UMissionWidget::OnMissionCompleted(FMissionData Mission)
{
	OnMissionCompletedAnim(Mission);
	RefreshMissions();
}

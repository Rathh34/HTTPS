#include "MainHUDWidget.h"
#include "HTTPSGameInstance.h"
#include "EventNotificationWidget.h"

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BindToGameInstance();
}

void UMainHUDWidget::BindToGameInstance()
{
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI)
	{
		UE_LOG(LogTemp, Warning, TEXT("[HUD] GameInstance not found in NativeConstruct"));
		return;
	}

	GI->OnWaveStarted.AddDynamic(this, &UMainHUDWidget::OnWaveStarted);
}

void UMainHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TimeSinceRefresh += InDeltaTime;
	if (TimeSinceRefresh < RefreshInterval) return;
	TimeSinceRefresh = 0.f;

	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;

	RefreshResourceBar(
		GI->GetResource(EResourceType::Acier),
		GI->GetResource(EResourceType::Quartz),
		GI->GetResource(EResourceType::Or),
		GI->GetResource(EResourceType::Biomasse),
		GI->GetResource(EResourceType::CadavreAlien)
	);

	RefreshEnergyBar(GI->TotalEnergyProduction, GI->TotalEnergyConsumption, GI->bBlackout);
	RefreshDroneBar(GI->TotalDrones, GI->AssignedDrones);
	RefreshPopulationBar(GI->Population, GI->HousingCapacity, GI->GetHappinessPercent());
	RefreshDate(GI->CurrentDay, GI->CurrentWeek, GI->CurrentMonth);
	RefreshReputation(GI->Reputation);

	// blackout flash — only fires on state change
	if (GI->bBlackout != bWasBlackout)
	{
		bWasBlackout = GI->bBlackout;
		if (GI->bBlackout) OnBlackoutStarted();
		else               OnBlackoutRestored();
	}
}

void UMainHUDWidget::OnWaveStarted(int32 WaveNumber, int32 WaveSize)
{
	if (EventNotification)
	{
		const FText Msg = FText::Format(
			FText::FromString(TEXT("Vague {0} — {1} aliens !")),
			FText::AsNumber(WaveNumber),
			FText::AsNumber(WaveSize)
		);
		EventNotification->ShowEvent(FText::FromString(TEXT("ATTAQUE")), Msg);
	}
}

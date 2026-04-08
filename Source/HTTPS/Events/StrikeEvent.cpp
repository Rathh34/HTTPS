#include "StrikeEvent.h"
#include "Colonists/WorkforceManager.h"
#include "Colonists/Colonist.h"
#include "Kismet/GameplayStatics.h"

void UStrikeEvent::Apply_Implementation(AActor* Context)
{
	AWorkforceManager* WM = Cast<AWorkforceManager>(
		UGameplayStatics::GetActorOfClass(Context->GetWorld(), AWorkforceManager::StaticClass())
	);
	if (!WM) return;

	TArray<AColonist*> All = WM->GetAllColonists();
	const int32 StrikeCount = FMath::RoundToInt(All.Num() * StrikeFraction);

	for (int32 i = 0; i < StrikeCount && i < All.Num(); i++)
		if (All[i] && All[i]->AssignedWorkplace)
			WM->UnassignFromWorkplace(All[i]->AssignedWorkplace);

	UE_LOG(LogTemp, Log, TEXT("[Strike] %d colonists walked off."), StrikeCount);
}

#include "ResearchLab.h"

void AResearchLab::OnOperational()
{
	// tiers are unlocked in GameInstance once the lab is built
	// UI reads UnlockedTiers to filter which nodes are accessible
	UE_LOG(LogTemp, Log, TEXT("[ResearchLab] Operational — %d tiers available"), UnlockedTiers.Num());
}

#include "ResearchManager.h"
#include "ResearchNode.h"
#include "ResearchTree.h"
#include "Resources/ResourceManager.h"

AResearchManager::AResearchManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool AResearchManager::UnlockNode(UResearchNode* Node)
{
	if (!Node || Node->bUnlocked || !ResourceManager) return false;

	for (UResearchNode* Prereq : Node->Prerequisites)
		if (!Prereq || !Prereq->bUnlocked) return false;

	for (const FResearchCost& Cost : Node->Cost)
		if (!ResourceManager->HasResource(Cost.Type, Cost.Amount)) return false;

	for (const FResearchCost& Cost : Node->Cost)
		ResourceManager->ConsumeResource(Cost.Type, Cost.Amount);

	Node->bUnlocked = true;
	OnResearchUnlocked.Broadcast(Node);
	UE_LOG(LogTemp, Log, TEXT("[Research] Unlocked: %s"), *Node->Name.ToString());
	return true;
}

bool AResearchManager::IsUnlocked(FName UnlockTag) const
{
	if (!Tree) return false;

	for (UResearchNode* Node : Tree->AllNodes)
		if (Node && Node->bUnlocked && Node->UnlockTag == UnlockTag)
			return true;

	return false;
}

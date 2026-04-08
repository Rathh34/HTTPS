#include "ResearchTree.h"
#include "ResearchNode.h"

TArray<UResearchNode*> UResearchTree::GetAvailableNodes() const
{
	TArray<UResearchNode*> Result;

	for (UResearchNode* Node : AllNodes)
	{
		if (!Node || Node->bUnlocked) continue;

		bool bPrereqsMet = true;
		for (UResearchNode* Prereq : Node->Prerequisites)
		{
			if (!Prereq || !Prereq->bUnlocked) { bPrereqsMet = false; break; }
		}

		if (bPrereqsMet) Result.Add(Node);
	}

	return Result;
}

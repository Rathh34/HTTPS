#include "ResearchWidget.h"
#include "ResearchNode.h"
#include "HTTPSGameInstance.h"

void UResearchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (GI) GI->OnNodeUnlocked.AddDynamic(this, &UResearchWidget::OnNodeUnlocked);
}

bool UResearchWidget::TryUnlockNode(UResearchNode* Node)
{
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return false;
	return GI->UnlockNode(Node);
}

bool UResearchWidget::IsNodeUnlocked(UResearchNode* Node) const
{
	if (!Node) return false;
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	return GI ? GI->IsUnlocked(Node->UnlockTag) : false;
}

bool UResearchWidget::CanUnlockNode(UResearchNode* Node) const
{
	if (!Node) return false;
	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return false;

	if (GI->IsUnlocked(Node->UnlockTag)) return false;
	if (GI->Population < Node->RequiredPopulation) return false;
	if (!GI->HasResource(EResourceType::Or, Node->GoldCost)) return false;

	for (const FName& Prereq : Node->Prerequisites)
		if (!GI->IsUnlocked(Prereq)) return false;

	return true;
}

void UResearchWidget::OnNodeUnlocked(FName Tag)
{
	OnNodeUnlockedAnim(Tag);
}

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResearchWidget.generated.h"

class UResearchNode;

// tech tree panel — BP handles tree layout and node buttons
UCLASS()
class HTTPS_API UResearchWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// called from BP node button OnClicked
	UFUNCTION(BlueprintCallable)
	bool TryUnlockNode(UResearchNode* Node);

	// whether a node is currently unlocked — used by BP to style node buttons
	UFUNCTION(BlueprintPure)
	bool IsNodeUnlocked(UResearchNode* Node) const;

	// whether a node can be unlocked right now
	UFUNCTION(BlueprintPure)
	bool CanUnlockNode(UResearchNode* Node) const;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnNodeUnlockedAnim(FName Tag);

private:
	UFUNCTION()
	void OnNodeUnlocked(FName Tag);
};

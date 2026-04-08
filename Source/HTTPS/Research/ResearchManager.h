#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResearchManager.generated.h"

class UResearchTree;
class UResearchNode;
class AResourceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResearchUnlocked, UResearchNode*, Node);

UCLASS()
class HTTPS_API AResearchManager : public AActor
{
	GENERATED_BODY()

public:
	AResearchManager();

	UPROPERTY(BlueprintAssignable)
	FOnResearchUnlocked OnResearchUnlocked;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Research")
	TObjectPtr<UResearchTree> Tree;

	UPROPERTY(EditAnywhere, Category = "Research")
	TObjectPtr<AResourceManager> ResourceManager;

	// deducts cost and unlocks — returns false if prereqs or resources missing
	UFUNCTION(BlueprintCallable)
	bool UnlockNode(UResearchNode* Node);

	// check by UnlockTag at runtime to gate features
	UFUNCTION(BlueprintPure)
	bool IsUnlocked(FName UnlockTag) const;
};

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NativeAIController.generated.h"

// runs BT_Native — key names must match the blackboard asset
UCLASS()
class HTTPS_API ANativeAIController : public AAIController
{
	GENERATED_BODY()

public:
	ANativeAIController();

	virtual void OnPossess(APawn* InPawn) override;

	static const FName TargetActorKey;
	static const FName HomeLocationKey;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
};

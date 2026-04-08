#include "NativeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ANativeAIController::TargetActorKey  = TEXT("TargetActor");
const FName ANativeAIController::HomeLocationKey = TEXT("HomeLocation");

ANativeAIController::ANativeAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANativeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		if (Blackboard)
			Blackboard->SetValueAsVector(HomeLocationKey, InPawn->GetActorLocation());
	}
}

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Colonist.generated.h"

UENUM(BlueprintType)
enum class EColonistState : uint8
{
	Idle,
	Assigned,
	Resting
};

UCLASS()
class HTTPS_API AColonist : public AActor
{
	GENERATED_BODY()

public:
	AColonist();

	UPROPERTY(BlueprintReadOnly)
	EColonistState State = EColonistState::Idle;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> AssignedWorkplace = nullptr;

	UFUNCTION(BlueprintCallable)
	void AssignTo(AActor* Workplace);

	UFUNCTION(BlueprintCallable)
	void Unassign();

	UFUNCTION(BlueprintPure)
	bool IsIdle() const { return State == EColonistState::Idle; }
};

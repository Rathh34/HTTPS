#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TaskComponent.generated.h"

UENUM(BlueprintType)
enum class ETaskType : uint8
{
	None,
	Harvesting,
	Building,
	Defending,
	Researching
};

// tracks what a colonist is currently doing
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HTTPS_API UTaskComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTaskComponent();

	UFUNCTION(BlueprintCallable)
	void SetTask(ETaskType NewTask, AActor* Workplace);

	UFUNCTION(BlueprintCallable)
	void ClearTask();

	UFUNCTION(BlueprintPure)
	ETaskType GetCurrentTask() const { return CurrentTask; }

	UFUNCTION(BlueprintPure)
	AActor* GetWorkplace() const { return CurrentWorkplace.Get(); }

private:
	UPROPERTY()
	ETaskType CurrentTask = ETaskType::None;

	UPROPERTY()
	TObjectPtr<AActor> CurrentWorkplace = nullptr;
};

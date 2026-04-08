#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomEventManager.generated.h"

class UEventBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventTriggered, UEventBase*, Event);

UCLASS()
class HTTPS_API ARandomEventManager : public AActor
{
	GENERATED_BODY()

public:
	ARandomEventManager();

	UPROPERTY(BlueprintAssignable)
	FOnEventTriggered OnEventTriggered;

	// populate in editor — anything added here can be picked
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Events")
	TArray<TSubclassOf<UEventBase>> EventPool;

	UPROPERTY(EditAnywhere, Category = "Events")
	float EventChancePerWeek = 0.4f;

	UFUNCTION(BlueprintCallable)
	void OnWeekPassed();

private:
	UEventBase* PickEvent() const;
};

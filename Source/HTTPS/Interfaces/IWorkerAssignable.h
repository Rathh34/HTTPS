#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWorkerAssignable.generated.h"

class AColonist;

UINTERFACE(MinimalAPI, BlueprintType)
class UWorkerAssignable : public UInterface { GENERATED_BODY() };

class HTTPS_API IWorkerAssignable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	bool AssignWorker(AColonist* Colonist);

	UFUNCTION(BlueprintNativeEvent)
	void RemoveWorker(AColonist* Colonist);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetMaxWorkers() const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetCurrentWorkerCount() const;
};

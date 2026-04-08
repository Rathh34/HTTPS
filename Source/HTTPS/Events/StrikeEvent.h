#pragma once

#include "CoreMinimal.h"
#include "EventBase.h"
#include "StrikeEvent.generated.h"

// fraction of assigned workers walk off the job
UCLASS()
class HTTPS_API UStrikeEvent : public UEventBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StrikeFraction = 0.3f;

	virtual void Apply_Implementation(AActor* Context) override;
};

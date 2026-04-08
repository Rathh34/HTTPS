#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventBase.generated.h"

// subclass and override Apply_Implementation
UCLASS(Abstract, BlueprintType, Blueprintable)
class HTTPS_API UEventBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText EventName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText EventDescription;

	// higher weight = more likely to be picked
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight = 1.f;

	UFUNCTION(BlueprintNativeEvent)
	void Apply(AActor* Context);
	virtual void Apply_Implementation(AActor* Context) {}
};

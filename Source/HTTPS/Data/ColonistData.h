#pragma once

#include "CoreMinimal.h"
#include "ColonistData.generated.h"

USTRUCT(BlueprintType)
struct FColonistData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	// contribution to workplace output — 1.0 = normal worker
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Efficiency = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100.f;
};

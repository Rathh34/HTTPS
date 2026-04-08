#pragma once

#include "CoreMinimal.h"
#include "NativeData.generated.h"

USTRUCT(BlueprintType)
struct FNativeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText TribeName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed = 300.f;

	// negative = hostile, positive = friendly
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InitialHostility = -50.f;
};

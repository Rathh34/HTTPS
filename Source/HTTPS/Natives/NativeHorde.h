#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NativeHorde.generated.h"

class ANativeBase;

// spawns and tracks a single wave
UCLASS()
class HTTPS_API ANativeHorde : public AActor
{
	GENERATED_BODY()

public:
	ANativeHorde();

	UPROPERTY(EditAnywhere, Category = "Horde")
	TSubclassOf<ANativeBase> NativeClass;

	UPROPERTY(EditAnywhere, Category = "Horde")
	int32 SpawnCount = 10;

	UPROPERTY(EditAnywhere, Category = "Horde")
	float SpawnRadius = 400.f;

	UFUNCTION(BlueprintCallable)
	void SpawnHorde();

	UFUNCTION(BlueprintPure)
	bool IsWipedOut() const { return AliveCount <= 0; }

private:
	int32 AliveCount = 0;

	UFUNCTION()
	void OnNativeDied(ANativeBase* Native);
};

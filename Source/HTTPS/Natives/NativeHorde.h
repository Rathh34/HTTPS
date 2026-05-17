#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NativeHorde.generated.h"

class ANativeBase;

UCLASS()
class HTTPS_API ANativeHorde : public AActor
{
	GENERATED_BODY()

public:
	ANativeHorde();

	UPROPERTY(EditAnywhere, Category = "Horde")
	TSubclassOf<ANativeBase> NativeClass;

	UPROPERTY(EditAnywhere, Category = "Horde")
	float SpawnRadius = 400.f;

	// called by GameInstance with the calculated wave size
	UFUNCTION(BlueprintCallable)
	void SpawnHorde(int32 Count);

	UFUNCTION(BlueprintPure)
	bool IsWipedOut() const { return AliveCount <= 0; }

private:
	int32 AliveCount = 0;

	UFUNCTION()
	void OnNativeDied();
};

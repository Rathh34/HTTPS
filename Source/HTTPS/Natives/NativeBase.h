#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NativeBase.generated.h"

class UHealthComponent;

// stats from GDD: 10 PV, 5 dmg, 0.5/s, 600cm/s
UCLASS()
class HTTPS_API ANativeBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANativeBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> HealthComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float AttackDamage = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float AttackRate = 0.5f; // attacks per second

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnDied();
};

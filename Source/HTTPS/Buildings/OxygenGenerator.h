#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IDamageable.h"
#include "OxygenGenerator.generated.h"

class UDomeComponent;

UCLASS()
class HTTPS_API AOxygenGenerator : public AActor, public IDamageable
{
	GENERATED_BODY()

public:
	AOxygenGenerator();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDomeComponent> Dome;

	UPROPERTY(EditAnywhere, Category = "Generator")
	float MaxHealth = 500.f;

	virtual void ApplyDamage_Implementation(float Amount, AActor* DamageSource) override;
	virtual float GetCurrentHealth_Implementation() const override { return CurrentHealth; }
	virtual bool IsAlive_Implementation() const override { return CurrentHealth > 0.f; }

protected:
	virtual void BeginPlay() override;

private:
	float CurrentHealth = 500.f;
};
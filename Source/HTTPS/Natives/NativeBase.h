#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IDamageable.h"
#include "Data/NativeData.h"
#include "NativeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNativeDied, ANativeBase*, Native);

UCLASS()
class HTTPS_API ANativeBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	ANativeBase();

	UPROPERTY(BlueprintAssignable)
	FOnNativeDied OnDied;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Native")
	FNativeData Data;

	virtual void ApplyDamage_Implementation(float Amount, AActor* DamageSource) override;
	virtual float GetCurrentHealth_Implementation() const override { return CurrentHealth; }
	virtual bool IsAlive_Implementation() const override { return CurrentHealth > 0.f; }

protected:
	virtual void BeginPlay() override;

private:
	float CurrentHealth = 100.f;

	void Die();
};

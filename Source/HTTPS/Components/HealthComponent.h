#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageReceived, float, Amount, AActor*, Source);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);

// shared by buildings, natives, dome — one impl for all
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HTTPS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth = 100.f;

	UPROPERTY(BlueprintAssignable)
	FOnDamageReceived OnDamageReceived;

	UPROPERTY(BlueprintAssignable)
	FOnDied OnDied;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float Amount, AActor* Source);

	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UFUNCTION(BlueprintPure)
	bool IsAlive() const { return CurrentHealth > 0.f; }

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const { return CurrentHealth / MaxHealth; }
};

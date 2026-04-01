#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "DomeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDomeDestroyed);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HTTPS_API UDomeComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UDomeComponent();

	virtual void OnRegister() override;

	UPROPERTY(BlueprintAssignable)
	FOnDomeDestroyed OnDomeDestroyed;

	UPROPERTY(EditAnywhere, Category = "Dome")
	float MaxHealth = 500.f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth = 500.f;

	UFUNCTION(BlueprintCallable)
	void TakeDomeDamage(float Amount);

	UFUNCTION(BlueprintCallable)
	void SetDomeRadius(float NewRadius);

	UFUNCTION(BlueprintPure)
	float GetDomeRadius() const { return GetScaledSphereRadius(); }

	UFUNCTION(BlueprintPure)
	bool IsInsideDome(FVector WorldPosition) const;

	UFUNCTION(BlueprintPure)
	bool IsDestroyed() const { return CurrentHealth <= 0.f; }
};
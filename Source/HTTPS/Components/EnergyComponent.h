#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnergyComponent.generated.h"

// positive EnergyDelta = producer, negative = consumer
// registers/unregisters with GameInstance on BeginPlay/EndPlay
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HTTPS_API UEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnergyComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	// positive = produces, negative = consumes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy")
	float EnergyDelta = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bActive = true;

	// toggle energy on/off for this building
	UFUNCTION(BlueprintCallable)
	void SetEnergyActive(bool bNewActive);

	UFUNCTION(BlueprintPure)
	bool IsProducer() const { return EnergyDelta > 0.f; }

private:
	void RegisterWithGameInstance(bool bRegister);
};

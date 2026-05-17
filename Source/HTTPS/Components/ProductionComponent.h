#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceType.h"
#include "ProductionComponent.generated.h"

class UDroneComponent;

// reads rate + type from owning building's data asset, scaled by drone efficiency
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HTTPS_API UProductionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UProductionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Production")
	EResourceType ProducedResource = EResourceType::Acier;

	// per second at 100% drone efficiency
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Production")
	float BaseProductionRate = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bEnabled = true;

	UFUNCTION(BlueprintCallable)
	void SetEnabled(bool bNewEnabled) { bEnabled = bNewEnabled; }

private:
	// cached ref set in BeginPlay
	UPROPERTY()
	TObjectPtr<UDroneComponent> DroneComp;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DomeExpansionManager.generated.h"

class UDomeComponent;
class AResourceManager;

UCLASS()
class HTTPS_API ADomeExpansionManager : public AActor
{
	GENERATED_BODY()

public:
	ADomeExpansionManager();

	UPROPERTY(EditAnywhere, Category = "Dome")
	float ExpansionCost = 100.f;

	UPROPERTY(EditAnywhere, Category = "Dome")
	float ExpansionRadiusIncrease = 500.f;

	// assign in editor — points to the OxygenGenerator's DomeComponent
	UPROPERTY(EditAnywhere, Category = "Dome")
	TObjectPtr<UDomeComponent> Dome;

	UPROPERTY(EditAnywhere, Category = "Dome")
	TObjectPtr<AResourceManager> ResourceManager;

	UFUNCTION(BlueprintCallable)
	bool TryExpand();

	UFUNCTION(BlueprintPure)
	float GetCurrentRadius() const;
};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiplomacyManager.generated.h"

class AResourceManager;

UENUM(BlueprintType)
enum class EDiplomacyStance : uint8
{
	Hostile,
	Neutral,
	Trading
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStanceChanged, EDiplomacyStance, NewStance);

UCLASS()
class HTTPS_API ADiplomacyManager : public AActor
{
	GENERATED_BODY()

public:
	ADiplomacyManager();

	UPROPERTY(BlueprintAssignable)
	FOnStanceChanged OnStanceChanged;

	UPROPERTY(BlueprintReadOnly)
	EDiplomacyStance CurrentStance = EDiplomacyStance::Hostile;

	// 0-100, high = hostile
	UPROPERTY(BlueprintReadOnly)
	float Hostility = 75.f;

	// costs Metal, lowers hostility
	UFUNCTION(BlueprintCallable)
	bool OfferTrade(float MetalCost);

	// destroys all natives and locks stance permanently
	UFUNCTION(BlueprintCallable)
	void Exterminate();

	UFUNCTION(BlueprintCallable)
	void ModifyHostility(float Delta);

	UPROPERTY(EditAnywhere, Category = "Diplomacy")
	TObjectPtr<AResourceManager> ResourceManager;

private:
	bool bExterminated = false;

	void UpdateStance();
};

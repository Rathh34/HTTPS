#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HTTPSGameState.generated.h"

UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	Setup,
	Playing,
	Win,
	Lose
};

UCLASS()
class HTTPS_API AHTTPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AHTTPSGameState();

	UPROPERTY(BlueprintReadOnly)
	int32 Population = 0;

	UPROPERTY(BlueprintReadOnly)
	float Reputation = 50.f;

	UPROPERTY(BlueprintReadOnly)
	EGamePhase CurrentPhase = EGamePhase::Setup;

	UFUNCTION(BlueprintCallable)
	void AddPopulation(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void ModifyReputation(float Delta);
};

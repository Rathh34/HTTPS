#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HTTPSGameState.generated.h"

UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	Playing,
	Win,
	Lose
};

// mirrors GameInstance data for UI binding — UI reads from here, not GameInstance directly
UCLASS()
class HTTPS_API AHTTPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AHTTPSGameState();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	int32 Population = 0;

	UPROPERTY(BlueprintReadOnly)
	float Reputation = 0.f;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentDay = 1;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentWeek = 1;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentMonth = 1;

	UPROPERTY(BlueprintReadOnly)
	EGamePhase Phase = EGamePhase::Playing;

	UFUNCTION(BlueprintCallable)
	void SetPhase(EGamePhase NewPhase);

private:
	// binds to GameInstance delegates to stay in sync
	void BindToGameInstance();

	UFUNCTION()
	void OnPopulationChanged(int32 NewPop, int32 HousingCap);

	UFUNCTION()
	void OnReputationChanged(float NewRep);

	UFUNCTION()
	void OnTimePassed(int32 Day, int32 Week, int32 Month);
};

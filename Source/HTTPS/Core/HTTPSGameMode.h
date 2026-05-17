#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HTTPSGameMode.generated.h"

UCLASS()
class HTTPS_API AHTTPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHTTPSGameMode();

	virtual void BeginPlay() override;

	// win condition — 1 million population
	UPROPERTY(EditAnywhere, Category = "Win")
	int32 WinPopulation = 1000000;
};

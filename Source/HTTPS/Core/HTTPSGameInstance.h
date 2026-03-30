#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HTTPSGameInstance.generated.h"

// persists across level loads (main menu -> planet)
UCLASS()
class HTTPS_API UHTTPSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float Reputation = 50.f;

	UPROPERTY(BlueprintReadWrite)
	int32 TotalWeeksElapsed = 0;
};
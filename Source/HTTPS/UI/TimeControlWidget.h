#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeControlWidget.generated.h"

// pause / x1 / x2 / x3 buttons
UCLASS()
class HTTPS_API UTimeControlWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetTimeScale(float Scale);

	UFUNCTION(BlueprintCallable)
	void Pause();

	UFUNCTION(BlueprintCallable)
	void Resume();

	UFUNCTION(BlueprintPure)
	float GetCurrentTimeScale() const;

	UFUNCTION(BlueprintPure)
	bool IsPaused() const { return GetCurrentTimeScale() <= 0.f; }
};

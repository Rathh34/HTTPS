#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventNotificationWidget.generated.h"

// popup for wave alerts and game events — starts Collapsed, auto-hides
UCLASS()
class HTTPS_API UEventNotificationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DisplayDuration = 4.f;

	UFUNCTION(BlueprintCallable)
	void ShowEvent(const FText& Title, const FText& Message);

protected:
	// BP plays appear animation here
	UFUNCTION(BlueprintImplementableEvent)
	void OnEventShown(const FText& Title, const FText& Message);

private:
	FTimerHandle HideTimer;

	void Hide();
};

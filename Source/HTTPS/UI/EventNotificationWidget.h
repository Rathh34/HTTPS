#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventNotificationWidget.generated.h"

// auto-hides after DisplayDuration — start visibility as Collapsed
UCLASS()
class HTTPS_API UEventNotificationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float DisplayDuration = 4.f;

	UFUNCTION(BlueprintCallable)
	void ShowEvent(const FText& Name, const FText& Description);

protected:
	// BP plays appear animation here
	UFUNCTION(BlueprintImplementableEvent)
	void OnEventShown(const FText& Name, const FText& Description);

private:
	FTimerHandle HideTimerHandle;

	void HideNotification();
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "HTTPSPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AHTTPSCameraPawn;
class UMainHUDWidget;

UCLASS()
class HTTPS_API AHTTPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHTTPSPlayerController();

	UFUNCTION(BlueprintPure)
	UMainHUDWidget* GetMainHUD() const { return MainHUDWidget; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_CameraMove;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_CameraZoom;

	// middle mouse hold
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_CameraRotate;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Select;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Cancel;

	// set in BP subclass to WBP_MainHUD
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMainHUDWidget> MainHUDClass;

private:
	void OnCameraMove(const FInputActionValue& Value);
	void OnCameraMoveCompleted(const FInputActionValue& Value);
	void OnCameraZoom(const FInputActionValue& Value);
	void OnRotateStart(const FInputActionValue& Value);
	void OnRotateEnd(const FInputActionValue& Value);
	void OnSelectPressed(const FInputActionValue& Value);
	void OnSelectReleased(const FInputActionValue& Value);
	void OnCancel(const FInputActionValue& Value);

	AHTTPSCameraPawn* GetCameraPawn() const;

	UPROPERTY()
	TObjectPtr<UMainHUDWidget> MainHUDWidget;

	bool bIsSelecting = false;
	bool bIsRotating  = false;
	FVector2D SelectionStart;
	FVector2D CameraMoveInput;
	FVector2D LastMousePos; // rotation polls delta in Tick
};

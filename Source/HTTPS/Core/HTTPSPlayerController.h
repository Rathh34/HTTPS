#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "HTTPSPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AHTTPSCameraPawn;

UCLASS()
class HTTPS_API AHTTPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHTTPSPlayerController();

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

	bool bIsSelecting = false;
	bool bIsRotating = false;
	FVector2D SelectionStart;
	FVector2D CameraMoveInput;
	FVector2D LastMousePos; // used to compute rotation delta in Tick
};
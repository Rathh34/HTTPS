#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HTTPSCameraPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class HTTPS_API AHTTPSCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	AHTTPSCameraPawn();

	void MoveCamera(FVector2D Direction, float DeltaTime);
	void ZoomCamera(float Value);
	void RotateCamera(FVector2D MouseDelta);

	UPROPERTY(EditAnywhere, Category = "Camera")
	float MoveSpeed = 1200.f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float EdgeScrollThreshold = 20.f;

	// zoom = spring arm length
	UPROPERTY(EditAnywhere, Category = "Camera")
	float ZoomSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float MinZoom = 400.f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxZoom = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float RotateSpeed = 0.3f;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> RootScene;

	// yaw on root, pitch on arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;

private:
	void HandleEdgeScroll(float DeltaTime);
};
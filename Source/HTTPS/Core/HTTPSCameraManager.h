#pragma once
 
#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "HTTPSCameraManager.generated.h"
 
UCLASS()
class HTTPS_API AHTTPSCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
 
public:
	AHTTPSCameraManager();
 
	virtual void UpdateCamera(float DeltaTime) override;
 
	void MoveCamera(FVector2D Direction, float DeltaTime);
	void ZoomCamera(float Value);
	void RotateCamera(FVector2D MouseDelta);
 
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MoveSpeed = 1200.f;
 
	UPROPERTY(EditAnywhere, Category = "Camera")
	float EdgeScrollThreshold = 20.f;
 
	UPROPERTY(EditAnywhere, Category = "Camera")
	float ZoomSpeed = 200.f;
 
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MinZoom = 400.f;
 
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxZoom = 3000.f;
 
	UPROPERTY(EditAnywhere, Category = "Camera")
	float RotateSpeed = 0.3f;
 
protected:
	virtual void UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime) override;
 
private:
	float CurrentZoom = 1400.f;
	FVector CameraPosition = FVector(0.f, 0.f, 1400.f);
	float CameraYaw = 0.f;
	float CameraPitch = -50.f;
 
	void HandleEdgeScroll(float DeltaTime);
};
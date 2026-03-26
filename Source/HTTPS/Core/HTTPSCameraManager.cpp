#include "HTTPSCameraManager.h"
#include "GameFramework/PlayerController.h"
 
AHTTPSCameraManager::AHTTPSCameraManager()
{
	ViewPitchMin = -70.f;
	ViewPitchMax = -30.f;
}
 
void AHTTPSCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);
	HandleEdgeScroll(DeltaTime);
}
 
void AHTTPSCameraManager::UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime)
{
	OutVT.POV.Location = CameraPosition;
	OutVT.POV.Rotation = FRotator(CameraPitch, CameraYaw, 0.f);
	OutVT.POV.FOV = DefaultFOV;
}
 
void AHTTPSCameraManager::MoveCamera(FVector2D Direction, float DeltaTime)
{
	FVector WorldDir = FRotator(0.f, CameraYaw, 0.f).RotateVector(
		FVector(Direction.X, Direction.Y, 0.f)
	);
	CameraPosition += WorldDir * MoveSpeed * DeltaTime;
}
 
void AHTTPSCameraManager::ZoomCamera(float Value)
{
	CurrentZoom = FMath::Clamp(CurrentZoom - Value * ZoomSpeed, MinZoom, MaxZoom);
	CameraPosition.Z = CurrentZoom;
}
 
void AHTTPSCameraManager::RotateCamera(FVector2D MouseDelta)
{
	CameraYaw += MouseDelta.X * RotateSpeed;
	CameraPitch = FMath::Clamp(CameraPitch - MouseDelta.Y * RotateSpeed, ViewPitchMin, ViewPitchMax);
}
 
void AHTTPSCameraManager::HandleEdgeScroll(float DeltaTime)
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC) return;
 
	float MouseX, MouseY;
	if (!PC->GetMousePosition(MouseX, MouseY)) return;
 
	int32 SizeX, SizeY;
	PC->GetViewportSize(SizeX, SizeY);
 
	FVector2D Dir = FVector2D::ZeroVector;
 
	if (MouseX <= EdgeScrollThreshold) Dir.Y = -1.f;
	else if (MouseX >= SizeX - EdgeScrollThreshold) Dir.Y = 1.f;
 
	if (MouseY <= EdgeScrollThreshold) Dir.X = 1.f;
	else if (MouseY >= SizeY - EdgeScrollThreshold) Dir.X = -1.f;
 
	if (!Dir.IsZero())
		MoveCamera(Dir, DeltaTime);
}
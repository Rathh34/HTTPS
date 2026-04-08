#include "HTTPSCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

AHTTPSCameraPawn::AHTTPSCameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	SpringArm->TargetArmLength = 1400.f;
	SpringArm->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch   = false; // pitch set manually via RotateCamera
	SpringArm->bInheritRoll    = false;
	SpringArm->bInheritYaw     = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void AHTTPSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleEdgeScroll(DeltaTime);
}

void AHTTPSCameraPawn::MoveCamera(FVector2D Direction, float DeltaTime)
{
	// rotate input by yaw so WASD always moves relative to camera facing
	const float Yaw = SpringArm->GetComponentRotation().Yaw;
	FVector WorldDir = FRotator(0.f, Yaw, 0.f).RotateVector(FVector(Direction.Y, Direction.X, 0.f));
	AddActorWorldOffset(WorldDir * MoveSpeed * DeltaTime);
}

void AHTTPSCameraPawn::ZoomCamera(float Value)
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength - Value * ZoomSpeed, MinZoom, MaxZoom);
}

void AHTTPSCameraPawn::RotateCamera(FVector2D MouseDelta)
{
	// yaw on root keeps move direction consistent after rotating
	FRotator NewRot = GetActorRotation();
	NewRot.Yaw += MouseDelta.X * RotateSpeed;
	SetActorRotation(NewRot);

	FRotator ArmRot = SpringArm->GetRelativeRotation();
	ArmRot.Pitch = FMath::Clamp(ArmRot.Pitch - MouseDelta.Y * RotateSpeed, -70.f, -30.f);
	SpringArm->SetRelativeRotation(ArmRot);
}

void AHTTPSCameraPawn::HandleEdgeScroll(float DeltaTime)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	float MouseX, MouseY;
	if (!PC->GetMousePosition(MouseX, MouseY)) return;

	int32 SizeX, SizeY;
	PC->GetViewportSize(SizeX, SizeY);

	FVector2D Dir = FVector2D::ZeroVector;

	if      (MouseX <= EdgeScrollThreshold)         Dir.X = -1.f;
	else if (MouseX >= SizeX - EdgeScrollThreshold) Dir.X =  1.f;
	if      (MouseY <= EdgeScrollThreshold)         Dir.Y =  1.f;
	else if (MouseY >= SizeY - EdgeScrollThreshold) Dir.Y = -1.f;

	if (!Dir.IsZero())
		MoveCamera(Dir, DeltaTime);
}

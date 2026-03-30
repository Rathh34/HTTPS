#include "HTTPSPlayerController.h"
#include "HTTPSCameraPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"

AHTTPSPlayerController::AHTTPSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AHTTPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AHTTPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(IA_CameraMove,   ETriggerEvent::Triggered,  this, &AHTTPSPlayerController::OnCameraMove);
		EIC->BindAction(IA_CameraMove,   ETriggerEvent::Completed,  this, &AHTTPSPlayerController::OnCameraMoveCompleted);
		EIC->BindAction(IA_CameraZoom,   ETriggerEvent::Triggered,  this, &AHTTPSPlayerController::OnCameraZoom);
		// Started/Completed because rotation polls mouse delta in Tick, not via input value
		EIC->BindAction(IA_CameraRotate, ETriggerEvent::Started,    this, &AHTTPSPlayerController::OnRotateStart);
		EIC->BindAction(IA_CameraRotate, ETriggerEvent::Completed,  this, &AHTTPSPlayerController::OnRotateEnd);
		EIC->BindAction(IA_Select,       ETriggerEvent::Started,    this, &AHTTPSPlayerController::OnSelectPressed);
		EIC->BindAction(IA_Select,       ETriggerEvent::Completed,  this, &AHTTPSPlayerController::OnSelectReleased);
		EIC->BindAction(IA_Cancel,       ETriggerEvent::Started,    this, &AHTTPSPlayerController::OnCancel);
	}
}

void AHTTPSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AHTTPSCameraPawn* CamPawn = GetCameraPawn();
	if (!CamPawn) return;

	if (!CameraMoveInput.IsZero())
		CamPawn->MoveCamera(CameraMoveInput, DeltaTime);

	if (bIsRotating)
	{
		FVector2D CurrentMouse;
		GetMousePosition(CurrentMouse.X, CurrentMouse.Y);
		CamPawn->RotateCamera(CurrentMouse - LastMousePos);
		LastMousePos = CurrentMouse;
	}
}

AHTTPSCameraPawn* AHTTPSPlayerController::GetCameraPawn() const
{
	return Cast<AHTTPSCameraPawn>(GetPawn());
}

void AHTTPSPlayerController::OnCameraMove(const FInputActionValue& Value)
{
	CameraMoveInput = Value.Get<FVector2D>();
}

void AHTTPSPlayerController::OnCameraMoveCompleted(const FInputActionValue& Value)
{
	CameraMoveInput = FVector2D::ZeroVector;
}

void AHTTPSPlayerController::OnCameraZoom(const FInputActionValue& Value)
{
	if (AHTTPSCameraPawn* CamPawn = GetCameraPawn())
		CamPawn->ZoomCamera(Value.Get<float>());
}

void AHTTPSPlayerController::OnRotateStart(const FInputActionValue& Value)
{
	bIsRotating = true;
	GetMousePosition(LastMousePos.X, LastMousePos.Y);
}

void AHTTPSPlayerController::OnRotateEnd(const FInputActionValue& Value)
{
	bIsRotating = false;
}

void AHTTPSPlayerController::OnSelectPressed(const FInputActionValue& Value)
{
	bIsSelecting = true;
	GetMousePosition(SelectionStart.X, SelectionStart.Y);
}

void AHTTPSPlayerController::OnSelectReleased(const FInputActionValue& Value)
{
	// ignore if we were rotating (middle mouse can overlap with selection logic)
	if (!bIsSelecting || bIsRotating) return;
	bIsSelecting = false;

	FVector2D SelectionEnd;
	GetMousePosition(SelectionEnd.X, SelectionEnd.Y);

	if (FVector2D::Distance(SelectionStart, SelectionEnd) < 10.f)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		UE_LOG(LogTemp, Warning, TEXT("Selected: %s"), *GetNameSafe(Hit.GetActor()));
	}
	// TODO: box select
}

void AHTTPSPlayerController::OnCancel(const FInputActionValue& Value)
{
	// TODO: deselect / cancel placement
}
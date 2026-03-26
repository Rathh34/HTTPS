#include "HTTPSGameMode.h"
#include "HTTPSPlayerController.h"

AHTTPSGameMode::AHTTPSGameMode()
{
	PlayerControllerClass = AHTTPSPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}

void AHTTPSGameMode::BeginPlay()
{
	Super::BeginPlay();
}

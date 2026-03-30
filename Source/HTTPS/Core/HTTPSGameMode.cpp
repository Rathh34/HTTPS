#include "HTTPSGameMode.h"
#include "HTTPSPlayerController.h"
#include "HTTPSCameraPawn.h"

AHTTPSGameMode::AHTTPSGameMode()
{
	PlayerControllerClass = AHTTPSPlayerController::StaticClass();
	DefaultPawnClass = AHTTPSCameraPawn::StaticClass();
}
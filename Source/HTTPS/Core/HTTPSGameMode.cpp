#include "HTTPSGameMode.h"
#include "HTTPSPlayerController.h"
#include "HTTPSCameraPawn.h"
#include "HTTPSGameState.h"

AHTTPSGameMode::AHTTPSGameMode()
{
	PlayerControllerClass = AHTTPSPlayerController::StaticClass();
	DefaultPawnClass = AHTTPSCameraPawn::StaticClass();
	GameStateClass = AHTTPSGameState::StaticClass();
}
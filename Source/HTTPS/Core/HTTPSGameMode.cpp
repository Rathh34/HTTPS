#include "HTTPSGameMode.h"
#include "HTTPSPlayerController.h"
#include "HTTPSCameraPawn.h"
#include "HTTPSGameState.h"
#include "HTTPSGameInstance.h"

AHTTPSGameMode::AHTTPSGameMode()
{
	PlayerControllerClass = AHTTPSPlayerController::StaticClass();
	DefaultPawnClass      = AHTTPSCameraPawn::StaticClass();
	GameStateClass        = AHTTPSGameState::StaticClass();
}

void AHTTPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	// kick off all game systems once the level is loaded
	if (UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>())
		GI->StartGame();
}

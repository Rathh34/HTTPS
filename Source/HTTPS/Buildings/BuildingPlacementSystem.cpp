#include "BuildingPlacementSystem.h"
#include "BuildingBase.h"
#include "Dome/DomeComponent.h"

ABuildingPlacementSystem::ABuildingPlacementSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingPlacementSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsPlacing) UpdatePreview();
}

void ABuildingPlacementSystem::StartPlacement(TSubclassOf<ABuildingBase> BuildingClass)
{
	if (!BuildingClass) return;
	CancelPlacement();

	PendingClass = BuildingClass;
	bIsPlacing   = true;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	PreviewActor = GetWorld()->SpawnActor<ABuildingBase>(BuildingClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);

	if (PreviewActor)
	{
		PreviewActor->SetActorEnableCollision(false);
		PreviewActor->PrimaryActorTick.bCanEverTick = false;
	}
}

void ABuildingPlacementSystem::ConfirmPlacement()
{
	if (!bIsPlacing || !PreviewActor || !bCanPlace) return;

	const FVector PlaceLoc = PreviewActor->GetActorLocation();
	PreviewActor->Destroy();
	PreviewActor = nullptr;
	bIsPlacing   = false;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ABuildingBase* NewBuilding = GetWorld()->SpawnActor<ABuildingBase>(PendingClass, PlaceLoc, FRotator::ZeroRotator, Params);
	if (NewBuilding)
	{
		OnBuildingPlaced.Broadcast(NewBuilding);
		UE_LOG(LogTemp, Log, TEXT("[Placement] Placed %s"), *GetNameSafe(NewBuilding));
	}
}

void ABuildingPlacementSystem::CancelPlacement()
{
	if (PreviewActor) PreviewActor->Destroy();
	PreviewActor = nullptr;
	bIsPlacing   = false;
	bCanPlace    = false;
}

FVector ABuildingPlacementSystem::GetCursorWorldLocation() const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return FVector::ZeroVector;

	FHitResult Hit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	return Hit.bBlockingHit ? Hit.Location : FVector::ZeroVector;
}

void ABuildingPlacementSystem::UpdatePreview()
{
	if (!PreviewActor) return;

	const FVector CursorLoc = GetCursorWorldLocation();
	PreviewActor->SetActorLocation(CursorLoc);

	bCanPlace = Dome ? Dome->IsInsideDome(CursorLoc) : true;
	// TODO: tint mesh green/red based on bCanPlace
}

#include "BuildingPlacementSystem.h"
#include "BuildingBase.h"
#include "BuildingData.h"
#include "HTTPSGameInstance.h"

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

	PendingClass     = BuildingClass;
	bIsPlacing       = true;
	bRotated         = false;
	CurrentFootprint = GetFootprintForClass(BuildingClass, false);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	PreviewActor = GetWorld()->SpawnActor<ABuildingBase>(BuildingClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);

	if (PreviewActor)
	{
		PreviewActor->SetActorEnableCollision(false);
		PreviewActor->SetActorTickEnabled(false);
		UE_LOG(LogTemp, Log, TEXT("[Placement] Started for %s"), *BuildingClass->GetName());
	}
}

void ABuildingPlacementSystem::ConfirmPlacement()
{
	if (!bIsPlacing || !bCanPlace || !PreviewActor) return;

	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;

	// check cost
	if (PreviewActor->BuildingData)
	{
		for (const FBuildingCost& Cost : PreviewActor->BuildingData->BuildCost)
		{
			if (!GI->HasResource(Cost.Type, Cost.Amount))
			{
				UE_LOG(LogTemp, Warning, TEXT("[Placement] Not enough resources"));
				return;
			}
		}
		for (const FBuildingCost& Cost : PreviewActor->BuildingData->BuildCost)
			GI->ConsumeResource(Cost.Type, Cost.Amount);
	}

	PreviewActor->SetActorEnableCollision(true);
	PreviewActor->SetActorTickEnabled(true);
	PreviewActor->OnPlaced(CurrentGridPos, bRotated);

	OnBuildingPlaced.Broadcast(PreviewActor);
	UE_LOG(LogTemp, Log, TEXT("[Placement] Placed %s at (%d,%d)"), *GetNameSafe(PreviewActor), CurrentGridPos.X, CurrentGridPos.Y);

	PreviewActor = nullptr;
	bIsPlacing   = false;
	bCanPlace    = false;
}

void ABuildingPlacementSystem::CancelPlacement()
{
	if (PreviewActor) PreviewActor->Destroy();
	PreviewActor = nullptr;
	bIsPlacing   = false;
	bCanPlace    = false;
	bRotated     = false;
}

void ABuildingPlacementSystem::RotatePlacement()
{
	if (!bIsPlacing) return;
	bRotated         = !bRotated;
	CurrentFootprint = GetFootprintForClass(PendingClass, bRotated);
}

FIntPoint ABuildingPlacementSystem::GetFootprintForClass(TSubclassOf<ABuildingBase> Class, bool bInRotated) const
{
	if (!Class) return FIntPoint(1, 1);
	ABuildingBase* CDO = Class->GetDefaultObject<ABuildingBase>();
	if (!CDO || !CDO->BuildingData) return FIntPoint(1, 1);

	const FIntPoint Base = CDO->BuildingData->FootprintSize;
	return bInRotated ? FIntPoint(Base.Y, Base.X) : Base;
}

FIntPoint ABuildingPlacementSystem::GetCursorGridPos() const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return FIntPoint::ZeroValue;

	FHitResult Hit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (!Hit.bBlockingHit) return FIntPoint::ZeroValue;

	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	return GI ? GI->WorldToGrid(Hit.Location) : FIntPoint::ZeroValue;
}

void ABuildingPlacementSystem::UpdatePreview()
{
	if (!PreviewActor) return;

	UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>();
	if (!GI) return;

	CurrentGridPos = GetCursorGridPos();
	const FVector WorldPos = GI->GridToWorld(CurrentGridPos);
	PreviewActor->SetActorLocation(WorldPos);

	// check placement validity
	const ETileZone Zone = PreviewActor->BuildingData ? PreviewActor->BuildingData->RequiredZone : ETileZone::Interior;
	bCanPlace = GI->CanPlaceBuilding(CurrentGridPos, CurrentFootprint, Zone);

	// TODO: tint preview mesh green/red based on bCanPlace
}

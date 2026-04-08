#include "NativeHorde.h"
#include "NativeBase.h"

ANativeHorde::ANativeHorde()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANativeHorde::SpawnHorde()
{
	if (!NativeClass) return;
	AliveCount = 0;

	for (int32 i = 0; i < SpawnCount; i++)
	{
		const FVector Offset   = FMath::VRand() * FMath::FRandRange(0.f, SpawnRadius);
		const FVector SpawnLoc = GetActorLocation() + FVector(Offset.X, Offset.Y, 0.f);

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ANativeBase* Native = GetWorld()->SpawnActor<ANativeBase>(NativeClass, SpawnLoc, FRotator::ZeroRotator, Params);
		if (Native)
		{
			Native->OnDied.AddDynamic(this, &ANativeHorde::OnNativeDied);
			AliveCount++;
		}
	}
}

void ANativeHorde::OnNativeDied(ANativeBase* Native)
{
	AliveCount = FMath::Max(0, AliveCount - 1);
}

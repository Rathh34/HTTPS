#include "DefenseBuilding.h"
#include "NativeBase.h"
#include "HealthComponent.h"
#include "DroneComponent.h"
#include "Kismet/GameplayStatics.h"

ADefenseBuilding::ADefenseBuilding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADefenseBuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ADefenseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsOperational() || DroneComp->AssignedDrones <= 0) return;

	TimeSinceLastShot += DeltaTime;
	if (TimeSinceLastShot < 1.f / FireRate) return;
	TimeSinceLastShot = 0.f;

	if (ANativeBase* Target = FindTargetInRange())
	{
		Target->HealthComp->ApplyDamage(DamagePerShot, this);

		// plasma penetration — hits the native behind the target too
		if (PenetrationDamage > 0.f)
		{
			// TODO: trace for second target in line
		}
	}
}

ANativeBase* ADefenseBuilding::FindTargetInRange() const
{
	// slow, but fine for now — revisit if native counts get high
	TArray<AActor*> Natives;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANativeBase::StaticClass(), Natives);

	for (AActor* A : Natives)
	{
		ANativeBase* Native = Cast<ANativeBase>(A);
		if (Native && Native->HealthComp->IsAlive() &&
			FVector::Dist(GetActorLocation(), Native->GetActorLocation()) <= AttackRange)
			return Native;
	}
	return nullptr;
}

#include "DefenseBuilding.h"
#include "Interfaces/IDamageable.h"
#include "Natives/NativeBase.h"
#include "Kismet/GameplayStatics.h"

ADefenseBuilding::ADefenseBuilding()
{
	MaxHealth        = 250.f;
	MaxWorkers       = 2;
	PowerConsumption = 10.f;
	PrimaryActorTick.bCanEverTick = true;
}

void ADefenseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsOperational() || AssignedWorkers.IsEmpty()) return;

	TimeSinceLastAttack += DeltaTime;
	if (TimeSinceLastAttack < FireRate) return;
	TimeSinceLastAttack = 0.f;

	if (AActor* Target = FindTargetInRange())
		IDamageable::Execute_ApplyDamage(Target, DamagePerSecond * FireRate, this);
}

AActor* ADefenseBuilding::FindTargetInRange() const
{
	// slow but fine for now, worth revisiting once native counts get high
	TArray<AActor*> Natives;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANativeBase::StaticClass(), Natives);

	for (AActor* Native : Natives)
		if (FVector::Dist(GetActorLocation(), Native->GetActorLocation()) <= AttackRange)
			return Native;

	return nullptr; // TODO: prioretize closest instead of first found
}

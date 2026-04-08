#include "MeteoriteEvent.h"
#include "Interfaces/IDamageable.h"
#include "Kismet/GameplayStatics.h"

void UMeteoriteEvent::Apply_Implementation(AActor* Context)
{
	UWorld* World = Context->GetWorld();
	if (!World) return;

	TArray<AActor*> Damageables;
	UGameplayStatics::GetAllActorsWithInterface(World, UDamageable::StaticClass(), Damageables);
	if (Damageables.IsEmpty()) return;

	const FVector ImpactPoint = Damageables[FMath::RandRange(0, Damageables.Num() - 1)]->GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("[Meteorite] Impact at %s"), *ImpactPoint.ToString());

	for (AActor* Actor : Damageables)
		if (FVector::Dist(Actor->GetActorLocation(), ImpactPoint) <= SplashRadius)
			IDamageable::Execute_ApplyDamage(Actor, Damage, nullptr);
}

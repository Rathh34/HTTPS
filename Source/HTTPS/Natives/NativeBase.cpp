#include "NativeBase.h"

ANativeBase::ANativeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANativeBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = Data.MaxHealth;
}

void ANativeBase::ApplyDamage_Implementation(float Amount, AActor* DamageSource)
{
	if (!IsAlive_Implementation()) return;

	CurrentHealth = FMath::Max(0.f, CurrentHealth - Amount);

	if (CurrentHealth <= 0.f)
		Die();
}

void ANativeBase::Die()
{
	OnDied.Broadcast(this);
	SetLifeSpan(2.f); // give BP time to play death anim before destroy
}

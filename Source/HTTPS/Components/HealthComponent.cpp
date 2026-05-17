#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UHealthComponent::ApplyDamage(float Amount, AActor* Source)
{
	if (!IsAlive() || Amount <= 0.f) return;

	CurrentHealth = FMath::Max(0.f, CurrentHealth - Amount);
	OnDamageReceived.Broadcast(Amount, Source);

	if (!IsAlive())
		OnDied.Broadcast();
}

void UHealthComponent::Heal(float Amount)
{
	if (!IsAlive() || Amount <= 0.f) return;
	CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + Amount);
}

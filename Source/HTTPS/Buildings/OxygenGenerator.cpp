#include "OxygenGenerator.h"
#include "Dome/DomeComponent.h"

AOxygenGenerator::AOxygenGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	Dome = CreateDefaultSubobject<UDomeComponent>(TEXT("Dome"));
	SetRootComponent(Dome);
}

void AOxygenGenerator::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void AOxygenGenerator::ApplyDamage_Implementation(float Amount, AActor* DamageSource)
{
	if (!IsAlive_Implementation()) return;

	CurrentHealth = FMath::Max(0.f, CurrentHealth - Amount);
	UE_LOG(LogTemp, Log, TEXT("[OxygenGenerator] Health: %.1f / %.1f"), CurrentHealth, MaxHealth);

	// damage passes through to dome — dome handles the game over logic
	Dome->TakeDomeDamage(Amount);
}

#include "DomeComponent.h"
#include "Core/HTTPSGameState.h"

UDomeComponent::UDomeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDomeComponent::OnRegister()
{
	Super::OnRegister();

	// safe here — would crash in constructor in UE5.7
	SetSphereRadius(1500.f);
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionResponseToAllChannels(ECR_Ignore);
	CurrentHealth = MaxHealth;
}

void UDomeComponent::TakeDomeDamage(float Amount)
{
	if (IsDestroyed()) return;

	CurrentHealth = FMath::Max(0.f, CurrentHealth - Amount);
	UE_LOG(LogTemp, Log, TEXT("[Dome] Health: %.1f / %.1f"), CurrentHealth, MaxHealth);

	if (IsDestroyed())
	{
		if (AHTTPSGameState* GS = GetWorld()->GetGameState<AHTTPSGameState>())
			GS->SetPhase(EGamePhase::Lose);

		OnDomeDestroyed.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("[Dome] Dome destroyed — game over."));
	}
}

void UDomeComponent::SetDomeRadius(float NewRadius)
{
	SetSphereRadius(FMath::Max(NewRadius, 100.f));
}

bool UDomeComponent::IsInsideDome(FVector WorldPosition) const
{
	return FVector::Dist(GetComponentLocation(), WorldPosition) <= GetDomeRadius();
}

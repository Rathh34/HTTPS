#include "NativeBase.h"
#include "HealthComponent.h"
#include "HTTPSGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

ANativeBase::ANativeBase()
{
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	HealthComp->MaxHealth = 10.f;

	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ANativeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthComp->OnDied.AddDynamic(this, &ANativeBase::OnDied);
}

void ANativeBase::OnDied()
{
	// register kill for missions before destroy
	if (UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>())
		GI->RegisterAlienKill();

	// cadavre drops handled here — TODO: spawn collectible or auto-add
	if (UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>())
		GI->AddResource(EResourceType::CadavreAlien, 1.f);

	SetLifeSpan(2.f); // give BP time for death anim
}

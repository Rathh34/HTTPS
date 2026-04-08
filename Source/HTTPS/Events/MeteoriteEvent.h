#pragma once

#include "CoreMinimal.h"
#include "EventBase.h"
#include "MeteoriteEvent.generated.h"

// picks a random damageable and hits everything in splash radius around it
UCLASS()
class HTTPS_API UMeteoriteEvent : public UEventBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SplashRadius = 300.f;

	virtual void Apply_Implementation(AActor* Context) override;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamageable.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

class HTTPS_API IDamageable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ApplyDamage(float Amount, AActor* DamageSource);

	UFUNCTION(BlueprintNativeEvent)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintNativeEvent)
	bool IsAlive() const;
};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceType.h"
#include "ResourceManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceChanged, EResourceType, Type, float, NewAmount);

UCLASS()
class HTTPS_API AResourceManager : public AActor
{
	GENERATED_BODY()

public:
	AResourceManager();

	UPROPERTY(BlueprintAssignable)
	FOnResourceChanged OnResourceChanged;

	UFUNCTION(BlueprintCallable)
	void AddResource(EResourceType Type, float Amount);

	// returns false and consumes nothing if not enough
	UFUNCTION(BlueprintCallable)
	bool ConsumeResource(EResourceType Type, float Amount);

	UFUNCTION(BlueprintPure)
	float GetResource(EResourceType Type) const;

	UFUNCTION(BlueprintPure)
	bool HasResource(EResourceType Type, float Amount) const;

private:
	UPROPERTY()
	TMap<EResourceType, float> Resources;
};
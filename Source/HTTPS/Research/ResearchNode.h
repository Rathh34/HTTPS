#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resources/ResourceType.h"
#include "ResearchNode.generated.h"

USTRUCT(BlueprintType)
struct FResearchCost
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EResourceType Type = EResourceType::ResearchPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Amount = 0.f;
};

UCLASS(BlueprintType, Blueprintable)
class HTTPS_API UResearchNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FResearchCost> Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UResearchNode>> Prerequisites;

	UPROPERTY(BlueprintReadOnly)
	bool bUnlocked = false;

	// checked by buildings/systems at runtime to gate features
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName UnlockTag;
};

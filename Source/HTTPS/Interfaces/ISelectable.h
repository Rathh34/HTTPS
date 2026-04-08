#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISelectable.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class USelectable : public UInterface { GENERATED_BODY() };

class HTTPS_API ISelectable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnSelected();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeselected();

	UFUNCTION(BlueprintNativeEvent)
	bool IsSelected() const;
};

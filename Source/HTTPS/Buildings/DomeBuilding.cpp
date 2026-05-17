#include "DomeBuilding.h"
#include "HTTPSGameInstance.h"

void ADomeBuilding::OnOperational()
{
	if (UHTTPSGameInstance* GI = GetGameInstance<UHTTPSGameInstance>())
		GI->SetDomeSize(InteriorSize);
}

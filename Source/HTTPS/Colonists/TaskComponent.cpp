#include "TaskComponent.h"

UTaskComponent::UTaskComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTaskComponent::SetTask(ETaskType NewTask, AActor* Workplace)
{
	CurrentTask      = NewTask;
	CurrentWorkplace = Workplace;
}

void UTaskComponent::ClearTask()
{
	CurrentTask      = ETaskType::None;
	CurrentWorkplace = nullptr;
}

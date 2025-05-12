// Jackie Lee .All Rights Reserved

#include "AbilitySystem/AbilityTasks/AbilityTask_ExecuteTaskOnTick.h"

/**
 * 构造函数
 * 初始化任务为可tick状态
 */
UAbilityTask_ExecuteTaskOnTick::UAbilityTask_ExecuteTaskOnTick()
{
	bTickingTask = true;
}

/**
 * 创建并返回一个每帧执行任务的能力任务实例
 * @param OwningAbility - 拥有此任务的能力实例
 * @return 返回创建的UAbilityTask_ExecuteTaskOnTick实例
 */
UAbilityTask_ExecuteTaskOnTick* UAbilityTask_ExecuteTaskOnTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	UAbilityTask_ExecuteTaskOnTick* Node = NewAbilityTask<UAbilityTask_ExecuteTaskOnTick>(OwningAbility);
	return Node;
}

/**
 * 每帧执行的任务函数
 * 重写自UAbilityTask/UGameplayTask
 * 如果任务应该广播委托,则广播OnAbilityTaskTick委托
 * 否则结束任务
 * @param DeltaTime - 帧间隔时间
 */
void UAbilityTask_ExecuteTaskOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTaskTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}

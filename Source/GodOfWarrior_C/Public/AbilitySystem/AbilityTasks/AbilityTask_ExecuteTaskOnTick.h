// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_ExecuteTaskOnTick.generated.h"

/**
 * 声明一个动态多播委托,用于在每帧执行时传递DeltaTime参数
 * @param DeltaTime - 帧间隔时间
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate, float, DeltaTime);

/**
 * 每帧执行任务的能力任务类
 * 继承自UAbilityTask,用于在游戏能力系统中实现每帧执行的功能
 * 通过委托机制允许蓝图或其他代码订阅每帧执行事件
 */
UCLASS()
class GODOFWARRIOR_C_API UAbilityTask_ExecuteTaskOnTick : public UAbilityTask
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	UAbilityTask_ExecuteTaskOnTick();

	/**
	 * 创建并返回一个每帧执行任务的能力任务实例
	 * @param OwningAbility - 拥有此任务的能力实例
	 * @return 返回创建的UAbilityTask_ExecuteTaskOnTick实例
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|AbilityTasks",
		meta=(HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly="true"))
	static UAbilityTask_ExecuteTaskOnTick* ExecuteTaskOnTick(UGameplayAbility* OwningAbility);

	/**
	 * 每帧执行的任务函数
	 * 重写自UAbilityTask/UGameplayTask
	 * @param DeltaTime - 帧间隔时间
	 */
	virtual void TickTask(float DeltaTime);

	/** 每帧执行时触发的委托 */
	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickDelegate OnAbilityTaskTick;
};

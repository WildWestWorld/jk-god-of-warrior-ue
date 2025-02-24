// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarriorGameplayAbility.generated.h"

class UPawnCombatComponent;
/**
 * 战士角色 能力激活策略枚举
 * 在蓝图中用于定义能力的激活时机
 */
// unit8 定义数据类型为uint8类型
UENUM(BlueprintType)
enum class EWarriorAbilityActivationPolicy : uint8
{
	/** 当特定条件满足时触发能力 */
	OnTriggered,

	/** 当能力被赋予角色时激活 */
	OnGiven
};

/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// 生命周期 来自 UGameplayAbility
	/**
	 * 当游戏能力系统将一个能力授予Actor时调用此函数
	 * 通常用于执行能力初始化相关的设置
	 * 
	 * @param ActorInfo - 包含拥有此能力的Actor的信息(如Avatar、Controller等)的数据结构
	 * @param Spec - 能力规格数据，包含能力等级、输入绑定等具体配置信息
	 */
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	/**
	* 终止能力时调用的函数。可以在此处理能力结束时的清理工作。
	* 
	* @param Handle - 能力规格句柄，用于唯一标识一个已赋予Actor的能力实例
	* @param ActorInfo - 包含拥有此能力的Actor信息(如Avatar、Controller等)的数据结构
	* @param ActivationInfo - 能力的激活信息，包含能力是如何被激活的详细数据
	* @param bReplicateEndAbility - 是否需要将能力结束的事件复制到其他客户端
	* @param bWasCancelled - 标识该能力是被取消的还是正常结束的
	*                        true表示被取消(如被打断)，false表示正常结束
	*/
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;


	//设置默认的激活策略
	//我们会在蓝图 里面更改默认的激活策略
	UPROPERTY(EditDefaultsOnly, Category="WarriorAbility")
	EWarriorAbilityActivationPolicy AbilityActivationPolicy = EWarriorAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category="Warrior|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;
};

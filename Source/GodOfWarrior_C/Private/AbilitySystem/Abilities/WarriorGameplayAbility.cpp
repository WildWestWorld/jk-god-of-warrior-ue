// Jackie Lee .All Rights Reserved

// 包含必要的头文件
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/Pawn/Combat/PawnCombatComponent.h"

/**
 * 当能力被授予时触发的函数
 * @param ActorInfo 包含拥有该能力的Actor相关信息的指针
 * @param Spec 能力的详细规格说明
 */
void UWarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilitySpec& Spec)
{
	// 调用父类的OnGiveAbility实现
	Super::OnGiveAbility(ActorInfo, Spec);

	// 检查能力的激活策略是否为"被授予时激活"
	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		// 确保ActorInfo有效且该能力当前未激活，没有激活就准备激活
		if (ActorInfo && !Spec.IsActive())
		{
			// 通过能力系统组件尝试激活该能力
			// Spec.Handle 是 FGameplayAbilitySpecHandle 类型，它是一个能力实例的唯一标识符（类似于身份证号码）。
			// Spec.Handle = Spec Id
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

// 生命周期 来自 UGameplayAbility
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
void UWarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         bool bReplicateEndAbility, bool bWasCancelled)
{
	// 调用父类的EndAbility实现，确保基础的能力终止逻辑得到执行
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	// 检查该能力是否为"给予时激活"的策略
	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		// 确保ActorInfo指针有效
		if (ActorInfo)
		{
			// 从能力系统组件中清除该能力
			// ClearAbility会完全移除这个能力，而不是仅仅停止激活状态
			// Handle 是 FGameplayAbilitySpecHandle 类型，它是一个能力实例的唯一标识符（类似于身份证号码）。
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

/**
 * 从ActorInfo中获取PawnCombatComponent组件
 * @return 返回拥有该能力的Actor的战斗组件指针
 */
UPawnCombatComponent* UWarriorGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	// 通过GetAvatarActorFromActorInfo获取Actor，然后查找并返回其UPawnCombatComponent组件
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

/**
 * 从ActorInfo中获取WarriorAbilitySystemComponent组件
 * @return 返回拥有该能力的Actor的能力系统组件指针
 */
UWarriorAbilitySystemComponent* UWarriorGameplayAbility::GetWarriorAbilitySystemComponentFromActorInfo() const
{
	// 将当前Actor的能力系统组件转换为WarriorAbilitySystemComponent类型并返回
	return Cast<UWarriorAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent	);
}
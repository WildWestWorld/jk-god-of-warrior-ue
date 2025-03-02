// Jackie Lee .All Rights Reserved


#include "AbilitySystem/WarriorAbilitySystemComponent.h"

/**
 * 处理技能输入按下事件
 * @param InInputTag - 与按下输入关联的游戏标签，用于识别具体是哪个技能输入
 */
void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	// 检查输入标签是否有效
	if (!InInputTag.IsValid())
	{
		return;
	}

	// 遍历所有可激活的技能
	for (const FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		// 检查技能的动态源标签是否与输入标签完全匹配
		// 如果不匹配则继续下一个技能
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
		
		// 尝试激活匹配的技能
		TryActivateAbility(AbilitySpec.Handle);
	}
}

/**
 * 处理技能输入释放事件
 * @param InInputTag - 与释放输入关联的游戏标签，用于识别具体是哪个技能输入
 */
void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

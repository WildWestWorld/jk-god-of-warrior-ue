// Jackie Lee .All Rights Reserved


#include "AbilitySystem/WarriorAbilitySystemComponent.h"

// 不加 AbilitySpec 用不了
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Debug/WarriorDebugHelper.h"

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
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
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


/**
 * 授予英雄武器相关的技能
 * 当英雄装备新武器时，将该武器相关的技能授予给英雄
 * 
 * @param InDefaultWeaponAbilities - 要授予的武器技能配置数组，包含技能类和对应的输入标签
 * @param ApplyLevel - 授予技能的等级，默认为1
 * @param OutGrantedAbilitySpecHandles - 输出参数，存储所有成功授予的技能句柄，用于后续管理这些技能
 */
void UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities(
	const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,
	TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	// 检查传入的技能数组是否为空，为空则直接返回
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}


	// 遍历每个武器技能配置，依次授予技能
	for (const FWarriorHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		// 检查技能配置是否有效（包含有效的技能类和输入标签）
		if (!AbilitySet.IsValid()) continue;


		// 使用技能类创建一个新的技能规格实例
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant.Get());


		// 设置技能的来源对象为当前角色（即技能系统组件所属的角色）
		AbilitySpec.SourceObject = GetAvatarActor();

		// 设置技能的等级，影响技能的威力或效果
		AbilitySpec.Level = ApplyLevel;

		// 为技能添加输入标签，这些标签用于将技能与特定的输入事件关联
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		// 将授予的技能句柄添加到输出数组中，确保不会重复添加相同的句柄
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}


void UWarriorAbilitySystemComponent::RemovedGrantedHeroWeaponAbilities(
	UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	// 检查传入的句柄数组是否为空,为空则直接返回
	if (InSpecHandlesToRemove.IsEmpty()) return;

	// 遍历每个技能句柄
	for (const FGameplayAbilitySpecHandle SpecHandle : InSpecHandlesToRemove)
	{
		// 检查技能句柄是否有效
		if (SpecHandle.IsValid())
		{
			// 移除该技能句柄对应的能力
			//ClearAbility该方法来自于 父组件UAbilitySystemComponent
			ClearAbility(SpecHandle);
		}
	}

	// 清空句柄数组,防止重复移除
	InSpecHandlesToRemove.Empty();
}

// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorAbilitySystemComponent.generated.h"

/**
 * 战士角色的技能系统组件
 * 继承自UAbilitySystemComponent，用于处理战士角色的技能系统相关功能
 * 主要功能包括:
 * - 处理技能输入事件(按下/释放)
 * - 管理和授予武器相关技能
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/**
	 * 处理技能输入按下事件
	 * 当玩家按下对应的输入键时触发
	 * 
	 * @param InInputTag - 与按下输入关联的游戏标签，用于识别具体是哪个技能输入
	 * 通过标签系统可以灵活地将输入映射到不同的技能上
	 */
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);

	/**
	 * 处理技能输入释放事件
	 * 当玩家释放对应的输入键时触发
	 * 
	 * @param InInputTag - 与释放输入关联的游戏标签，用于识别具体是哪个技能输入
	 * 配合按下事件可以实现按住释放等复杂的技能触发机制
	 */
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	/**
	 * 授予英雄武器相关的技能
	 * 可在蓝图中调用，用于动态给角色添加武器技能
	 * 
	 * @param InDefaultWeaponAbilities - 要授予的武器技能配置数组，包含技能类和对应的输入标签
	 * @param ApplyLevel - 授予技能的等级，默认值为1
	 * @param OutGrantedAbilitySpecHandles - 输出参数，用于存储授予的技能特征句柄
	 * 
	 * 通常在切换武器或初始化角色装备时调用
	 * 该函数会将传入的技能配置转换为实际的游戏能力并授予给角色
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability", meta=(ApplyLevel ="1"))
	void GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,
	                              TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	/**
	 * 移除已授予的英雄武器技能
	 * 可在蓝图中调用，用于动态移除角色的武器技能
	 * 
	 * @param InSpecHandlesToRemove - 要移除的技能特征句柄数组，传入要移除的技能句柄列表
	 *        使用UPARAM(ref)标记该参数为引用传递，这样在蓝图中调用时:
	 *        - 可以直接修改原始数组内容
	 *        - 避免数组复制带来的性能开销
	 *        - 保证函数内对数组的修改能反映到调用处
	 * 
	 * 通常在以下情况调用:
	 * - 切换武器时移除旧武器的技能
	 * - 卸下武器时移除相关技能
	 * - 角色死亡时清理技能
	 * 
	 * 该函数会遍历传入的句柄数组，依次移除对应的游戏能力
	 * 移除后这些技能将无法再次使用，除非重新授予
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void RemovedGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);
};

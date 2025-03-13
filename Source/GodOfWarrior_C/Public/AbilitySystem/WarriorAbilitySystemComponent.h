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
	 * @param ApplyLevel - 授予技能的等级，在元数据中显示默认值提示为1
	 * @param OutGrantedAbilitySpecHandles
	 * 
	 * 通常在切换武器或初始化角色装备时调用
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability", meta=(ApplyLevel ="1"))
	void GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,
	                              TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);
};

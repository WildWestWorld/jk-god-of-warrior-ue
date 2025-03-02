// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarriorAbilitySystemComponent.generated.h"

/**
 * 战士角色的技能系统组件
 * 继承自UAbilitySystemComponent，用于处理战士角色的技能系统相关功能
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/**
	 * 处理技能输入按下事件
	 * @param InInputTag - 与按下输入关联的游戏标签，用于识别具体是哪个技能输入
	 */
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);

	/**
	 * 处理技能输入释放事件
	 * @param InInputTag - 与释放输入关联的游戏标签，用于识别具体是哪个技能输入
	 */
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);
};

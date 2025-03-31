// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UGameplayEffect;
class UWarriorAbilitySystemComponent;
class UWarriorGameplayAbility;

/**
 * 数据资产基类，用于管理启动时的能力系统数据
 * 该类作为数据容器，存储和管理游戏启动时需要初始化的能力数据
 * 主要功能包括：
 * - 存储需要在启动时激活的能力
 * - 存储响应性能力（按需激活）
 * - 提供能力授予接口
 */
UCLASS()
class GODOFWARRIOR_C_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * 将数据资产中定义的能力赋予指定的能力系统组件
	 * 该函数会处理两类能力：立即激活能力和响应性能力
	 * 
	 * @param InASCToGive - 接收能力的战士能力系统组件实例
	 * @param ApplyLevel - 能力的应用等级，用于初始化能力的等级属性，默认为1级
	 */
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	/** 
	 * 需要立即激活的能力数组
	 * 这些能力会在调用GiveToAbilitySystemComponent时自动授予并激活
	 * 适用于：
	 * - 基础移动能力
	 * - 默认状态效果
	 * - 持续性被动技能
	 */
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;

	/** 
	 * 响应性能力数组
	 * 这些能力在授予后不会立即激活，需要满足特定条件才会触发
	 * 适用于：
	 * - 技能组合
	 * - 触发性技能
	 * - 条件触发的被动效果
	 */
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

	/**
	 * 静态辅助函数，用于实际执行能力授予操作
	 * 
	 * @param InAbilitiesToGive - 待授予的能力类数组
	 * @param InASCToGive - 目标能力系统组件
	 * @param ApplyLevel - 能力应用等级
	 */
	static void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
	                           UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

	/**
	 * 启动时需要应用的游戏效果数组
	 * 这些效果会在游戏开始时自动应用到角色身上
	 * 用于设置角色的初始状态、属性修改器等持续性效果
	 */
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;
};

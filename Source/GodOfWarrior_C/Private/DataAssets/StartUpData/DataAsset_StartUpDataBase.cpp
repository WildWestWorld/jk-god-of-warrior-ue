// Jackie Lee .All Rights Reserved

/**
 * 代码逻辑说明:
 * 1. 数据资产基类的主要实现，负责能力授予的核心逻辑
 * 2. 执行流程：
 *    - GiveToAbilitySystemComponent作为对外接口，接收目标ASC和等级参数
 *    - 分别对立即激活能力和响应性能力执行GrantAbilities
 *    - GrantAbilities遍历能力数组，为每个能力创建spec并授予给ASC
 * 3. 安全性考虑：
 *    - 使用check确保ASC有效
 *    - 检查能力数组是否为空
 *    - 验证每个能力类是否有效
 */

#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

/**
 * 将当前数据资产中的所有能力赋予指定的能力系统组件
 * 该函数会依次处理立即激活能力和响应性能力
 * 
 * @param InWarriorASCToGive - 目标能力系统组件，必须是有效的
 * @param ApplyLevel - 能力的应用等级，影响能力初始化时的等级属性
 */
void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive,
                                                              int32 ApplyLevel)
{
    // 确保传入的目标能力系统组件 有效
    check(InWarriorASCToGive);
    
    // 依次授予两类能力
    GrantAbilities(ActivateOnGivenAbilities, InWarriorASCToGive, ApplyLevel);
    GrantAbilities(ReactiveAbilities, InWarriorASCToGive, ApplyLevel);
}

/**
 * 静态辅助函数，执行实际的能力授予操作
 * 为指定的能力系统组件授予一组能力
 * 
 * @param InAbilitiesToGive - 待授予的能力类数组
 * @param InWarriorASCToGive - 目标能力系统组件
 * @param ApplyLevel - 能力的应用等级
 * 
 * 实现细节：
 * 1. 检查能力数组是否为空
 * 2. 遍历每个能力类
 * 3. 为每个有效的能力创建AbilitySpec
 * 4. 设置Spec的源对象为ASC的Avatar
 * 5. 设置能力等级
 * 6. 将能力授予给ASC
 */
void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
                                                UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel)
{
    // 如果能力数组为空，直接返回
    if (InAbilitiesToGive.IsEmpty())
    {
       return;
    }

    // 遍历所有待授予的能力
    for (const TSubclassOf<UWarriorGameplayAbility>& Ability : InAbilitiesToGive)
    {
       // 跳过无效的能力类
       if (!Ability) continue;

       // 创建能力规格
       FGameplayAbilitySpec AbilitySpec(Ability);
       // 设置能力的源对象为角色
       AbilitySpec.SourceObject = InWarriorASCToGive->GetAvatarActor();
       // 设置能力等级
       AbilitySpec.Level = ApplyLevel;

       // 将能力授予给目标能力系统组件 
       InWarriorASCToGive->GiveAbility(AbilitySpec);
    }
}
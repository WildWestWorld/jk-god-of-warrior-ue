// Jackie Lee .All Rights Reserved


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

/**
 * 将数据资产中定义的能力赋予指定的能力系统组件
 * 该函数会遍历并应用所有敌人战斗能力
 * 
 * @param InASCToGive - 接收能力的能力系统组件实例
 * @param ApplyLevel - 能力的应用等级，用于初始化能力的等级属性，默认为1级
 */
void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
                                                               int32 ApplyLevel)
{
	// 首先调用父类的实现
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	// 检查敌人战斗能力数组是否为空
	if (!EnemyCombatAbilities.IsEmpty())
	{
		// 遍历所有敌人战斗能力
		for (const TSubclassOf<UWarriorGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			// 跳过无效的能力类
			if (!AbilityClass) continue;
			
			// 创建能力规格实例
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			// 设置能力来源为拥有该能力系统组件的角色
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();

			// 设置能力等级
			AbilitySpec.Level = ApplyLevel;
			// 将能力赋予能力系统组件
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}

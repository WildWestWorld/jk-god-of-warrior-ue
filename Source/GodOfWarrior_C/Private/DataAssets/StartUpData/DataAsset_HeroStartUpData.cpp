// Jackie Lee .All Rights Reserved


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"


/**
 * 将英雄初始技能授予给指定的技能系统组件
 * 
 * @param InASCToGive - 目标技能系统组件
 * @param ApplyLevel - 技能等级，默认为1
 * 
 * 实现步骤:
 * 1. 调用父类的授予方法
 * 2. 遍历所有英雄初始技能配置
 * 3. 对每个有效的技能配置:
 *    - 创建技能规格(AbilitySpec)
 *    - 设置来源对象、等级和输入标签
 *    - 将技能授予给目标ASC
 */
void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
                                                              int32 ApplyLevel)
{
	// 首先调用父类的授予方法
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	// 遍历所有英雄初始技能配置
	for (const FWarriorHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		// 跳过无效的技能配置
		if (!AbilitySet.IsValid())
		{
			continue;
		}
		
		// 创建技能规格并设置相关属性
		// 使用技能类创建技能规格实例
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		// 设置技能的来源对象为拥有ASC的Actor
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		// 设置技能等级
		AbilitySpec.Level = ApplyLevel;
		// 将输入标签添加到技能规格的动态标签中，用于后续的输入绑定
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		// 将技能授予给目标ASC
		InASCToGive->GiveAbility(AbilitySpec);
	}
}

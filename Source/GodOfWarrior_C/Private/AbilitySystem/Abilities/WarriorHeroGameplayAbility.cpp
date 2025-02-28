// Jackie Lee .All Rights Reserved

#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"

/**
 * 从ActorInfo中获取英雄角色实例
 * 如果缓存的英雄角色指针无效，则尝试从CurrentActorInfo中获取并缓存
 * 使用弱指针缓存以避免循环引用
 * @return 返回缓存的英雄角色指针，如果无效则返回nullptr
 */
AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	// 检查缓存的英雄角色指针是否有效
	if (!CachedWarriorHeroCharacter.IsValid())
	{
		// 从CurrentActorInfo的AvatarActor中获取并缓存英雄角色
		// AvatarActor代表当前拥有该技能的角色实例
		CachedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	// 返回缓存的英雄角色指针，如果无效则返回nullptr
	// 使用三元运算符进行空值检查
	return CachedWarriorHeroCharacter.IsValid() ? CachedWarriorHeroCharacter.Get() : nullptr;
}

/**
 * 从ActorInfo中获取英雄控制器实例
 * 如果缓存的控制器指针无效，则尝试从CurrentActorInfo中获取并缓存
 * 使用弱指针缓存以避免循环引用
 * @return 返回缓存的控制器指针，如果无效则返回nullptr
 */
AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	// 检查缓存的控制器指针是否有效
	if (!CachedWarriorHeroController.IsValid())
	{
		// 从CurrentActorInfo的PlayerController中获取并缓存控制器
		// PlayerController代表当前控制该角色的控制器实例
		CachedWarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController);
	}
	// 返回缓存的控制器指针，如果无效则返回nullptr
	// 使用三元运算符进行空值检查
	return CachedWarriorHeroController.IsValid() ? CachedWarriorHeroController.Get() : nullptr;
}

/**
 * 从ActorInfo中获取英雄战斗组件实例
 * 通过调用GetHeroCharacterFromActorInfo()获取英雄角色，然后获取其战斗组件
 * @return 返回英雄角色的战斗组件指针
 */
UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	//GetHeroCharacterFromActorInfo 就是我们上面的自己写的方法
	// 获取英雄角色的战斗组件并返回
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

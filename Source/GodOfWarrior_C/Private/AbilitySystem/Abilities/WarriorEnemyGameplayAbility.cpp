// Jackie Lee .All Rights Reserved


#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"

#include "Characters/WarriorEnemyCharacter.h"

/**
 * 从ActorInfo中获取敌人角色
 * 
 * 该函数首先检查缓存的敌人角色指针是否有效:
 * 1. 如果无效,则从CurrentActorInfo中获取AvatarActor并转换为敌人角色类型
 * 2. 将转换后的结果缓存起来以提高后续访问性能
 * 
 * @return 返回敌人角色指针,如果转换失败则返回nullptr
 */
AWarriorEnemyCharacter* UWarriorEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedWarriorEnemyCharacter.IsValid())
	{
		//CurrentActorInfo 来自于GPlayAbility 我们继承自他
		CachedWarriorEnemyCharacter = Cast<AWarriorEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedWarriorEnemyCharacter.IsValid() ? CachedWarriorEnemyCharacter.Get() : nullptr;
}

/**
 * 从ActorInfo中获取敌人的战斗组件
 * 
 * 该函数通过调用GetEnemyCharacterFromActorInfo获取敌人角色,
 * 然后访问该角色的战斗组件
 * 
 * @return 返回敌人角色的战斗组件指针
 */
UEnemyCombatComponent* UWarriorEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

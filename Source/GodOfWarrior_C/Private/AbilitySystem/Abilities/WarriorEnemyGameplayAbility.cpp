// Jackie Lee .All Rights Reserved


#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Characters/WarriorEnemyCharacter.h"
#include "GameplayTags/WarriorGameplayTags.h"

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

FGameplayEffectSpecHandle UWarriorEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);
	// 获取技能系统组件
	UAbilitySystemComponent* AbilitySystemComponent = GetWarriorAbilitySystemComponentFromActorInfo();
	AActor* AvatarActor = GetAvatarActorFromActorInfo();


	// 创建效果上下文并设置相关参数
	// - 设置当前技能为效果来源
	// - 设置角色为源对象和发起者
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(AvatarActor);
	ContextHandle.AddInstigator(AvatarActor, AvatarActor);

	// 使用技能系统组件创建外发效果规范
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		EffectClass, GetAbilityLevel(), ContextHandle);

	// 设置效果的基础伤害值
	EffectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage,
	                                               InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));

	return EffectSpecHandle;
}

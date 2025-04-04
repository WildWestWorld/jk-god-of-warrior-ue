// Jackie Lee .All Rights Reserved

#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "GameplayTags/WarriorGameplayTags.h"

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

/**
 * 创建英雄伤害效果规范句柄
 * 用于构建伤害效果的规范,包含伤害计算所需的各项参数
 * 
 * @param EffectClass - 要应用的GameplayEffect效果类
 * @param InWeaponBaseDamage - 武器的基础伤害值
 * @param InCurrentAttackTypeTag - 当前攻击类型的GameplayTag
 * @param InDisplayComboCount - 当前连击数
 * @return 返回配置好的GameplayEffect规范句柄
 */
FGameplayEffectSpecHandle UWarriorHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag,
	int32 InDisplayComboCount)
{
	// 确保传入的效果类有效
	check(EffectClass);

	// 获取技能系统组件
	UAbilitySystemComponent* AbilitySystemComponent = GetWarriorAbilitySystemComponentFromActorInfo();
	if (!AbilitySystemComponent)
	{
		return FGameplayEffectSpecHandle();
	}

	// 获取拥有该技能的角色
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor)
	{
		return FGameplayEffectSpecHandle();
	}

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

	// 检查效果规范是否创建成功
	if (!EffectSpecHandle.IsValid())
	{
		return FGameplayEffectSpecHandle();
	}

	// 设置效果的基础伤害值
	EffectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);
	
	// 如果攻击类型标签有效,设置当前连击数
	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InDisplayComboCount);
	}

	// 返回配置好的效果规范句柄
	return EffectSpecHandle;
}

// Jackie Lee .All Rights Reserved


#include "Components/Pawn/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Chaos/Deformable/MuscleActivationConstraints.h"
#include "Debug/WarriorDebugHelper.h"
#include "GameplayTags/WarriorGameplayTags.h"
#include "Items/Weapons/WarriorHeroWeapon.h"

/**
 * 通过GameplayTag获取英雄携带的武器
 * 该函数调用父类的GetCharacterCarriedWeaponByTag方法获取基础武器，
 * 然后将其转换为英雄专用武器类型AWarriorHeroWeapon
 * 
 * @param InWeaponTag - 要获取的武器的GameplayTag标识符
 * @return 返回转换后的英雄武器指针，如果转换失败则返回nullptr
 */
AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	// 调用父类方法获取基础武器，并尝试将其转换为英雄武器类型
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

/**
 * 获取英雄当前装备的武器
 * 该函数调用父类的GetCharacterCurrentEquippedWeapon方法获取基础武器，
 * 然后将其转换为英雄专用武器类型AWarriorHeroWeapon
 * 
 * @return 返回转换后的英雄武器指针，如果转换失败则返回nullptr
 */
AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

/**
 * 获取英雄当前装备武器在指定等级下的伤害值
 * 通过访问武器数据中的基础伤害曲线，获取特定等级下的伤害值
 * 
 * @param InLevel - 要查询的等级
 * @return 返回武器在指定等级下的伤害值
 */
float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

/**
 * 当武器击中目标角色时调用的函数
 * 用于处理武器击中效果和发送相关游戏事件
 * 
 * @param HitActor - 被武器击中的目标角色
 */
void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// 检查目标角色是否已经在重叠列表中
	// 如果已存在则直接返回,避免重复处理同一目标
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	// 将新击中的目标添加到重叠列表中
	OverlappedActors.AddUnique(HitActor);

	// 创建游戏事件数据
	FGameplayEventData EventData;
	// 设置事件发起者为当前拥有武器的Pawn
	EventData.Instigator = GetOwningPawn();
	// 设置事件目标为被击中的角色
	EventData.Target = HitActor;

	// 向拥有者发送近战命中事件
	// 这将触发相关的游戏效果(如伤害计算、特效播放等)
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),
	                                                         WarriorGameplayTags::Shared_Event_MeleeHit, EventData);


	// 向拥有者发送击中暂停事件
	// 这将触发游戏暂停效果,增强打击感
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),
	                                                         WarriorGameplayTags::Player_Event_HitPause,
	                                                         FGameplayEventData());
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),
	                                                         WarriorGameplayTags::Player_Event_HitPause,
	                                                         FGameplayEventData());
}

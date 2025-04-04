// Jackie Lee .All Rights Reserved

#include "Components/Pawn/Combat/PawnCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Debug/WarriorDebugHelper.h"
#include "Items/Weapons/WarriorWeaponBase.h"

/**
 * 注册一个生成的武器到角色的武器映射表中
 * @param InWeaponTagToRegister - 要注册的武器的GameplayTag
 * @param InWeaponToRegister - 要注册的武器实例指针
 * @param bRegisterAsEquippedWeapon - 是否将该武器注册为当前装备的武器
 */
void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
                                                 AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	// 检查该武器标签是否已经在映射表中存在
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister),
	       TEXT("A named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());

	// 检查武器标签是否有效
	checkf(InWeaponTagToRegister.IsValid(),
	       TEXT("Invalid weapon tag provided"));

	// 检查武器指针是否有效
	checkf(IsValid(InWeaponToRegister),
	       TEXT("Invalid weapon pointer provided"));

	// CharacterCarriedWeaponMap 看起来是一个存储武器信息的映射
	// Emplace 是一个函数，用于在映射中插入新的元素
	// InWeaponTagToRegister 是键（Key），可能是用来标识武器的标签或ID
	// InWeaponToRegister 是值（Value），可能是实际的武器对象或引用

	// 将武器添加到映射表中
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	// 如果需要将该武器设置为当前装备的武器
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

/**
 * 通过GameplayTag获取角色携带的武器
 * @param InWeaponTagToGet - 要获取的武器的GameplayTag
 * @return 返回找到的武器指针，如果未找到则返回nullptr
 */
AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	// 检查映射表中是否包含该武器标签
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		// 尝试从映射表中找到对应的武器
		if (AWarriorWeaponBase* const * FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}

/**
 * 获取角色当前装备的武器
 * @return 返回当前装备的武器指针，如果没有装备武器则返回nullptr
 */
AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	// 检查当前装备的武器标签是否有效
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	// 通过当前装备的武器标签获取武器实例
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

/**
 * 切换武器的碰撞检测状态
 * @param bShouldEnable - 是否启用碰撞检测
 * @param ToggleDamageType - 指定要切换碰撞的武器类型
 */
void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	// 如果是当前装备的武器
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		// 获取当前装备的武器
		AWarriorWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();
		// 确保武器存在
		check(WeaponToToggle);

		if (bShouldEnable)
		{
			// 启用武器的碰撞检测,设置为只进行查询
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled((ECollisionEnabled::QueryOnly));
		}
		else
		{
			// 禁用武器的碰撞检测
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled((ECollisionEnabled::NoCollision));
		}
	}
	//TODO:加个碰撞体积盒子
}

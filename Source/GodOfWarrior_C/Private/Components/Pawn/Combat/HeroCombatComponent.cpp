// Jackie Lee .All Rights Reserved


#include "Components/Pawn/Combat/HeroCombatComponent.h"

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

// Jackie Lee .All Rights Reserved


#include "Items/Weapons/WarriorHeroWeapon.h"

/**
 * 分配能力特征句柄到武器
 * 
 * @param InSpecHandles - 要分配给武器的能力特征句柄数组
 * 该函数将传入的能力特征句柄数组赋值给武器的GrantedAbilitySpecHandles成员变量
 * 用于更新武器当前拥有的能力特征集合
 */
void AWarriorHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

/**
 * 获取武器当前拥有的所有能力特征句柄
 * 
 * @return 返回存储在GrantedAbilitySpecHandles中的能力特征句柄数组
 * 该函数用于查询武器当前具有的所有能力特征
 * 返回的是一个只读副本，不会影响原始数据
 */
TArray<FGameplayAbilitySpecHandle> AWarriorHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}

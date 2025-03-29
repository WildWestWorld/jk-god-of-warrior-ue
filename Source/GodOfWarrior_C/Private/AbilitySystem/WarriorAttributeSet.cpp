// Jackie Lee .All Rights Reserved


#include "AbilitySystem/WarriorAttributeSet.h"

/**
 * 构造函数,初始化角色的基础属性值
 * 所有属性初始值设为1.0
 * 包括:
 * - 当前生命值
 * - 最大生命值  
 * - 当前怒气值
 * - 最大怒气值
 * - 攻击力
 * - 防御力
 */
UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);  // 初始化当前生命值
	InitMaxHealth(1.f);      // 初始化最大生命值
	InitCurrentRage(1.f);    // 初始化当前怒气值
	InitMaxRage(1.f);        // 初始化最大怒气值
	InitAttackPower(1.f);    // 初始化攻击力
	InitDefencePower(1.f);   // 初始化防御力
}

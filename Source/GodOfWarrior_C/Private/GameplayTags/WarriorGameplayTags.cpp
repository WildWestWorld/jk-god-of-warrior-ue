// Jackie Lee .All Rights Reserved

#include "GameplayTags/WarriorGameplayTags.h"

/**
 * WarriorGameplayTags命名空间的实现
 * 在这里定义所有在头文件中声明的GameplayTag
 */
namespace WarriorGameplayTags
{
	// UE_DEFINE_GAMEPLAY_TAG 是一个宏，它在 Unreal Engine (UE) 中用于定义和注册游戏标签。游戏标签是用来标识和分类游戏中的不同事件或状态。
	// 	这段代码定义了两个游戏标签（Gameplay Tags）：
	// InputTag_Move：该标签的值为 "InputTag.Move"。
	// InputTag_Look：该标签的值为 "InputTag.Look"。
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipAxe, "InputTag.EquipAxe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquipAxe, "InputTag.UnEquipAxe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Axe, "InputTag.LightAttack.Axe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Axe, "InputTag.HeavyAttack.Axe")

	//Ability Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UnEquip_Axe, "Player.Ability.UnEquip.Axe")

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Axe, "Player.Ability.Attack.Light.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Axe, "Player.Ability.Attack.Heavy.Axe")

	
	//Weapon Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe, "Player.Weapon.Axe")

	//Event Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe, "Player.Event.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_Axe, "Player.Event.UnEquip.Axe")
}

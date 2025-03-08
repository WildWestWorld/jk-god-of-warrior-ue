// Jackie Lee .All Rights Reserved

#pragma once

#include "NativeGameplayTags.h"

/**
 * WarriorGameplayTags命名空间
 * 用于定义游戏中所有的GameplayTag（游戏标签）
 * GameplayTag系统用于标记和识别游戏中的各种状态、动作和事件
 */
namespace WarriorGameplayTags
{
	// 当你在构建 GODOFWARRIOR 模块时，GODOFWARRIOR_C_API 会被定义为 __declspec(dllexport)，表示将 InputTag_Move 和 InputTag_Look 导出到 DLL 中。也就是添加变量
	// 当其他模块引用这些标签时，GODOFWARRIOR_C_API 会被定义为 __declspec(dllimport)，表示从 DLL 导入这些标签。也就是使用变量

	// UE_DECLARE_GAMEPLAY_TAG_EXTERN 是 Unreal Engine 中的宏，它用于声明一个游戏标签的外部引用。
	// 该宏告诉编译器，InputTag_Move 和 InputTag_Look 将在其他地方定义，而不是在当前文件中定义。
	GODOFWARRIOR_C_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	GODOFWARRIOR_C_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)

	GODOFWARRIOR_C_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe)
	GODOFWARRIOR_C_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnEquipAxe)

	// Player Tags
	GODOFWARRIOR_C_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)
	GODOFWARRIOR_C_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	GODOFWARRIOR_C_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip_Axe);
}

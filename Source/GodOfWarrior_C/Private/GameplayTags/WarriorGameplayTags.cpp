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
}

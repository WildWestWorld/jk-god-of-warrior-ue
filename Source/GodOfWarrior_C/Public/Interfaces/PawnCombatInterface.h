// Jackie Lee .All Rights Reserved

/**
 * 代码逻辑说明:
 * 1. 这是一个Pawn战斗接口类，用于定义战斗相关的接口功能
 * 2. 包含两个主要部分:
 *    - UPawnCombatInterface: 接口的UObject包装类，用于UE4反射系统
 *    - IPawnCombatInterface: 实际的接口类，包含需要实现的虚函数
 * 3. 实现该接口的类需要:
 *    - 继承IPawnCombatInterface
 *    - 实现所有纯虚函数
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnCombatInterface.generated.h"

class UPawnCombatComponent;
// 接口的UObject包装类，不需要修改
UINTERFACE(MinimalAPI)
class UPawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 战斗接口类
 * 定义了与战斗系统相关的核心接口函数
 * 所有需要战斗功能的Pawn类都应该实现这个接口
 */
class GODOFWARRIOR_C_API IPawnCombatInterface
{
	GENERATED_BODY()

public:
	/**
	 * 获取Pawn的战斗接口实例
	 * @return 返回实现了该接口的UObject指针
	 * 注意：继承类必须实现此纯虚函数
	 * = 0 - 表示这是一个纯虚函数，必须由继承这个接口的类来实现
	 */
	virtual UPawnCombatComponent* GetPawnCombatComponent() const = 0;
};

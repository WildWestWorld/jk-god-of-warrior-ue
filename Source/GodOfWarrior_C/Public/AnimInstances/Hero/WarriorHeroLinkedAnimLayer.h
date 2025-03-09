// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorHeroAnimInstance.h"
#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "WarriorHeroLinkedAnimLayer.generated.h"

/**
 * 英雄角色动画链接层类
 * 该类用于连接和管理英雄角色的动画实例
 * 继承自基础动画实例类 UWarriorBaseAnimInstance
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorHeroLinkedAnimLayer : public UWarriorBaseAnimInstance
{
	GENERATED_BODY()

public:
	/**
	 * 获取英雄角色动画实例的方法
	 * @return 返回英雄角色动画实例的指针
	 * @note 该函数在蓝图中是纯函数，是线程安全的
	 */
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UWarriorHeroAnimInstance* GetHeroAnimInstance() const;
};

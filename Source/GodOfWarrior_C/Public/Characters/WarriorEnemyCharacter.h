// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorEnemyCharacter.generated.h"

class UEnemyCombatComponent;
/**
 * 敌人角色类
 * 继承自AWarriorBaseCharacter基类
 * 实现了游戏中敌人角色的基本功能
 */
UCLASS()
class GODOFWARRIOR_C_API AWarriorEnemyCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()

public:
	/**
	 * 构造函数
	 * 初始化敌人角色的基本属性和组件
	 */
	AWarriorEnemyCharacter();

protected:
	/**
	 * 敌人战斗组件
	 * 处理敌人的战斗相关功能,如攻击、受伤等
	 * VisibleAnywhere: 组件在所有地方可见
	 * BlueprintReadOnly: 蓝图中只读访问
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

public:
	/**
	 * 获取敌人战斗组件的访问器
	 * @return 返回敌人战斗组件的指针
	 * FORCEINLINE: 强制内联以提高性能
	 */
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};

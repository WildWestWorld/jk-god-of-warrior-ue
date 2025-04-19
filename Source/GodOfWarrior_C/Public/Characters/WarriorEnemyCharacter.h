// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorEnemyCharacter.generated.h"

class UWidgetComponent;
class UEnemyUIComponent;
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


	//来自于BaseCharacter/IPawnCombatInterface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	//来自于来自于BaseCharacter/IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//来自于来自于BaseCharacter/IPawnUIInterface
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;

protected:
	/**
	 * 敌人战斗组件
	 * 处理敌人的战斗相关功能,如攻击、受伤等
	 * VisibleAnywhere: 组件在所有地方可见
	 * BlueprintReadOnly: 蓝图中只读访问
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

	/**
	 * 当角色被控制器占有时调用
	 * 重写自父类的虚函数
	 * 用于在AI控制器开始控制该敌人角色时进行初始化设置
	 * 
	 * @param NewController - 接管控制的新控制器实例
	 */
	virtual void PossessedBy(AController* NewController) override;

	virtual void BeginPlay() override;

private:
	void InitEnemyStartUpData();

public:
	/**
	 * 获取敌人战斗组件的访问器
	 * @return 返回敌人战斗组件的指针
	 * FORCEINLINE: 强制内联以提高性能
	 */
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};

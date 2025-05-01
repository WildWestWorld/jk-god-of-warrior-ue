// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "WarriorEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AWarriorEnemyCharacter;

/**
 * 敌人角色的游戏能力基类
 * 继承自UWarriorGameplayAbility,为敌人角色提供特定的能力功能
 * 包含获取敌人角色和战斗组件的辅助函数
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorEnemyGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()

public:
	/**
	 * 从ActorInfo中获取敌人角色
	 * @return 返回拥有该能力的敌人角色指针
	 * BlueprintPure: 表示这是一个纯函数,不会修改任何状态
	 */
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarriorEnemyCharacter* GetEnemyCharacterFromActorInfo();

	/**
	 * 从ActorInfo中获取敌人的战斗组件
	 * @return 返回敌人角色的战斗组件指针
	 * BlueprintPure: 表示这是一个纯函数,不会修改任何状态
	 */
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
	                                                          const FScalableFloat& InDamageScalableFloat);

private:
	// 缓存的敌人角色弱指针,用于优化性能
	// 使用弱指针避免循环引用导致的内存泄漏
	TWeakObjectPtr<AWarriorEnemyCharacter> CachedWarriorEnemyCharacter;
};

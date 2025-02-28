// Jackie Lee 版权所有

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Components/Pawn/Combat/HeroCombatComponent.h"
#include "WarriorHeroGameplayAbility.generated.h"

// 英雄控制器类的前向声明
class AWarriorHeroController;
// 英雄角色类的前向声明
class AWarriorHeroCharacter;

/**
 * 英雄角色游戏技能的基类
 * 继承自UWarriorGameplayAbility以提供英雄角色特定的技能功能
 * 包含获取英雄角色和控制器引用的辅助方法
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorHeroGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()

public:
	/**
	 * 从ActorInfo中获取英雄角色实例
	 * 如果缓存的英雄角色指针无效，则尝试从CurrentActorInfo中获取并缓存
	 * @return 返回拥有此技能的英雄角色指针，如果获取失败则返回nullptr
	 * BlueprintPure：表示这是一个纯函数，不修改任何状态，可以安全地从蓝图中调用
	 */
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarriorHeroCharacter* GetHeroCharacterFromActorInfo();

	/**
	 * 从ActorInfo中获取英雄控制器实例
	 * @return 返回控制此英雄角色的控制器指针
	 * BlueprintPure：表示这是一个纯函数，不修改任何状态，可以安全地从蓝图中调用
	 */
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarriorHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

private:
	/**
	 * 缓存的英雄角色弱指针
	 * 使用弱指针以避免循环引用并允许正确的对象清理
	 * 通过GetHeroCharacterFromActorInfo()方法访问和更新
	 */
	TWeakObjectPtr<AWarriorHeroCharacter> CachedWarriorHeroCharacter;

	/**
	 * 缓存的英雄控制器弱指针
	 * 使用弱指针以避免循环引用并允许正确的对象清理
	 * 通过GetHeroControllerFromActorInfo()方法访问和更新
	 */
	TWeakObjectPtr<AWarriorHeroController> CachedWarriorHeroController;

};

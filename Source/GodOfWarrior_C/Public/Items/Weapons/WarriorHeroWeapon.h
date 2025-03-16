// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorHeroWeapon.generated.h"

/**
 * 英雄武器类
 * 继承自WarriorWeaponBase基类，用于实现具体的英雄武器功能
 */
UCLASS()
class GODOFWARRIOR_C_API AWarriorHeroWeapon : public AWarriorWeaponBase
{
	GENERATED_BODY()

public:
	/**
	 * 武器数据属性
	 * 包含武器的基本属性数据，如伤害、特效等
	 * 数据结构定义在WarriorStructTypes中
	 * 可在蓝图中编辑默认值，但运行时只能读取
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWarriorHeroWeaponData HeroWeaponData;

	/**
	 * 分配能力特征句柄
	 * @param InSpecHandles - 要分配的能力特征句柄数组
	 * 可在蓝图中调用，用于设置武器的能力特征
	 */
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	/**
	 * 获取已分配的能力特征句柄
	 * @return 返回当前武器拥有的所有能力特征句柄
	 * BlueprintPure表示这是一个纯函数，不会修改任何状态
	 */
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	/** 
	 * 存储武器当前拥有的能力特征句柄
	 * 用于追踪和管理武器具有的游戏能力
	 */
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};

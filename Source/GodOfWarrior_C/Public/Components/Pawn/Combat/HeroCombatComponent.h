// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Pawn/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AWarriorHeroWeapon;
/**
 * UHeroCombatComponent 用于管理英雄角色的战斗系统
 * 继承自UPawnCombatComponent，专门处理英雄角色的战斗相关功能
 * 主要功能包括:
 * - 管理英雄角色特有的武器系统
 * - 提供英雄武器查询接口
 */
UCLASS()
class GODOFWARRIOR_C_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	/**
	 * 通过GameplayTag获取英雄携带的武器
	 * @param InWeaponTag - 要获取的武器的GameplayTag
	 * @return 返回找到的英雄武器指针，如果未找到则返回nullptr
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;


	/**
	 * 获取英雄当前装备的武器
	 * @return 返回当前装备的英雄武器指针，如果未装备武器则返回nullptr
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	/**
	 * 获取英雄当前装备武器在指定等级下的伤害值
	 * @param InLevel - 要查询的等级
	 * @return 返回武器在指定等级下的伤害值
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

	/**
	 * 当武器击中目标角色时调用
	 * @param HitActor - 被击中的目标角色
	 */
	virtual void OnHitTargetActor(AActor* HitActor) override;

	/**
	 * 当武器从目标角色身上拔出时调用
	 * @param InteractedActor - 与武器交互的目标角色
	 */
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};

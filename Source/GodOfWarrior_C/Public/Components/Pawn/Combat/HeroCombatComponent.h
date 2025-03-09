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
};

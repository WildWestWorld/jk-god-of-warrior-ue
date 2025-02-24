// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/Pawn/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AWarriorWeaponBase;

/**
* UPawnCombatComponent 用于管理角色的战斗系统
* 主要功能包括:
* - 管理角色携带的武器
* - 处理武器的装备状态
* - 提供武器查询接口
*/
UCLASS()
class GODOFWARRIOR_C_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	/**
	 * 注册一个生成的武器到角色的武器映射表中
	 * @param InWeaponTagToRegister - 要注册的武器的GameplayTag
	 * @param InWeaponToRegister - 要注册的武器实例指针
	 * @param bRegisterAsEquippedWeapon - 是否将该武器注册为当前装备的武器
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister,
							   bool bRegisterAsEquippedWeapon = false);

	/**
	 * 通过GameplayTag获取角色携带的武器
	 * @param InWeaponTagToGet - 要获取的武器的GameplayTag
	 * @return 返回找到的武器指针，如果未找到则返回nullptr
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	/** 当前装备的武器的GameplayTag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warrior|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	/**
	 * 获取角色当前装备的武器
	 * @return 返回当前装备的武器指针，如果没有装备武器则返回nullptr
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCurrentEquippedWeapon() const;

private:
	/** 存储角色携带的所有武器，key为武器的GameplayTag，value为武器实例指针 */
	TMap<FGameplayTag, AWarriorWeaponBase*> CharacterCarriedWeaponMap;
};
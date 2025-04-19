// Jackie Lee .All Rights Reserved

#pragma once
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
// USTRUCT 结构体必须包含生成的头文件才能编译
#include "WarriorStructTypes.generated.h"

// 前向声明所需的类
class UInputMappingContext;
class UWarriorHeroLinkedAnimLayer;
class UWarriorHeroGameplayAbility;


/**
 * 英雄技能配置结构体
 * 用于配置英雄初始技能及其对应的输入标签
 * 在 DataAsset_HeroStartUpData 中使用
 */
USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
	GENERATED_BODY()

	// 技能对应的输入标签，用于将技能与特定输入绑定
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	// 要授予的技能类，指定英雄可以获得的具体技能
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarriorHeroGameplayAbility> AbilityToGrant;

	// 检查技能配置是否有效
	bool IsValid() const;
};


/**
 * 英雄武器数据结构
 * 用于存储和管理英雄武器相关的数据
 * 可在蓝图中使用
 *  在 AWarriorHeroWeapon 中使用
 */
USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
	GENERATED_BODY()

	/**
	 * 武器动画层类引用
	 * 用于指定该武器使用的动画层类
	 * 可在编辑器默认值中设置，蓝图中只读
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarriorHeroLinkedAnimLayer> WeaponAnimLayerToLink;

	// 武器控制的输入映射上下文
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	// 装备此武器时授予的默认技能数组
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FWarriorHeroAbilitySet> DefaultWeaponAbilities;

	//默认武器的伤害
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};

// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_HeroStartUpData.generated.h"

/**
 * 英雄技能配置结构体
 * 用于配置英雄初始技能及其对应的输入标签
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
	TSubclassOf<UWarriorGameplayAbility> AbilityToGrant;

	// 检查技能配置是否有效
	bool IsValid() const;
};

/**
 * 英雄初始数据资产类
 * 继承自基础初始数据资产类
 * 用于配置英雄的初始技能集
 */
UCLASS()
class GODOFWARRIOR_C_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	/**
	 * 将配置的技能授予给指定的技能系统组件
	 * @param InASCToGive - 目标技能系统组件
	 * @param ApplyLevel - 技能等级，默认为1
	 */
	virtual void
	GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	// 英雄初始技能集数组，包含所有要授予英雄的技能配置
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta=(TitleProperty="InputTag"))
	TArray<FWarriorHeroAbilitySet> HeroStartUpAbilitySets;
};

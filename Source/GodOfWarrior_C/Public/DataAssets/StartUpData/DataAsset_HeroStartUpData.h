// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"


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

// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

/**	
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	/** 覆盖父方法，这个方法父级也有
 * 将数据资产中定义的能力赋予指定的能力系统组件
 * 该函数会处理两类能力：立即激活能力和响应性能力
 * 
 * @param InASCToGive - 接收能力的战士能力系统组件实例
 * @param ApplyLevel - 能力的应用等级，用于初始化能力的等级属性，默认为1级
 */
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> EnemyCombatAbilities;
};

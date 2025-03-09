// Jackie Lee .All Rights Reserved

#pragma once
// USTRUCT 必须要声明下面这个 不然无法编译
#include "WarriorStructTypes.generated.h"
class UWarriorHeroLinkedAnimLayer;
/**
 * 英雄武器数据结构
 * 用于存储和管理英雄武器相关的数据
 * 可在蓝图中使用
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
};

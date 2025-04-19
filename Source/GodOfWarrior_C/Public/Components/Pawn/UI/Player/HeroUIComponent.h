// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Pawn/UI/PawnUIComponent.h"
#include "HeroUIComponent.generated.h"

/**
 * 声明一个动态多播委托,用于通知装备武器改变事件
 * @param SoftWeaponIcon - 新武器的图标纹理引用
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>,
                                            SoftWeaponIcon);

/**
 * 英雄角色的UI组件类
 * 继承自PawnUIComponent,用于处理英雄特有的UI相关功能
 * 包括怒气值变化和武器装备变化的事件通知
 */
UCLASS()
class GODOFWARRIOR_C_API UHeroUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	/** 
	 * 当前怒气值改变时触发的委托
	 * 继承自PawnUIComponent的FOnPercentChangedDelegate类型
	 * 用于通知UI更新怒气值显示
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;

	/**
	 * 当装备武器改变时触发的委托
	 * 可在蓝图中分配和调用
	 * 用于通知UI更新武器图标显示
	 */
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;
};

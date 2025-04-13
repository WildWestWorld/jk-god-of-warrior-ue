 // Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Pawn/PawnExtensionComponentBase.h"
#include "PawnUIComponent.generated.h"

/**
 * 声明一个动态多播委托类型，用于通知百分比变化
 * @param NewPercent - 新的百分比值
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent);

/**
 * Pawn UI组件基类
 * 提供基础的UI相关功能，如生命值显示等
 * 可被具体的Pawn类型(如英雄、敌人等)继承和扩展
 */
UCLASS()
class GODOFWARRIOR_C_API UPawnUIComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	/** 
	 * 当前生命值改变时触发的委托
	 * 可在蓝图中绑定以更新UI显示
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentHealthChanged;
};

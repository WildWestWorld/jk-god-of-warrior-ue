// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OrientToTargetActor.generated.h"

/**
 * 行为树服务节点类,用于控制AI朝向目标Actor
 * 
 * 主要功能:
 * - 从黑板中获取目标Actor
 * - 使AI平滑地旋转朝向目标
 * - 提供可配置的旋转插值速度
 */
UCLASS()
class GODOFWARRIOR_C_API UBTService_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()

	/** 构造函数,初始化服务节点的基本属性 */
	UBTService_OrientToTargetActor();

	/** 
	 * 从行为树资产初始化服务节点
	 * @param Asset - 所属的行为树资产
	 */
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	/**
	 * 获取节点的静态描述文本
	 * @return FString - 描述该服务节点功能的文本
	 */
	virtual FString GetStaticDescription() const override;

	/**
	 * 服务节点的周期性更新函数
	 * @param OwnerComp - 拥有该节点的行为树组件
	 * @param NodeMemory - 节点内存
	 * @param DeltaSeconds - 帧间隔时间
	 */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** 
	 * 黑板中目标Actor的键选择器
	 * 用于指定要朝向的目标Actor
	 */
	UPROPERTY(EditAnywhere, Category="Target")
	FBlackboardKeySelector InTargetActorKey;

	/**
	 * 旋转插值速度
	 * 控制AI转向目标时的平滑程度
	 * 值越大,转向越快;值越小,转向越平滑
	 */
	UPROPERTY(EditAnywhere, Category="Target")
	float RotationInterpSpeed;
};

// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RotateToFaceTarget.generated.h"

/**
 * 任务内存结构体，用于存储旋转朝向目标所需的数据
 * 包含:
 * - OwningPawn: 执行该任务的AI角色
 * - TargetActor: 需要朝向的目标Actor
 */
struct FRotateToFaceTargetTaskMemory
{
	/** 执行该任务的AI角色 */
	TWeakObjectPtr<APawn> OwningPawn;
	/** 需要朝向的目标Actor */
	TWeakObjectPtr<AActor> TargetActor;

	/** 检查内存数据是否有效 */
	bool IsValid() const
	{
		return OwningPawn.IsValid() && TargetActor.IsValid();
	}

	/** 重置内存数据 */
	void Reset()
	{
		OwningPawn.Reset();
		TargetActor.Reset();
	}
};

/**
 * 行为树任务节点类，用于控制AI旋转朝向目标
 * 
 * 主要功能:
 * - 从黑板中获取目标Actor
 * - 使AI平滑地旋转朝向目标
 * - 提供可配置的旋转精度和插值速度
 */
UCLASS()
class GODOFWARRIOR_C_API UBTTask_RotateToFaceTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
	/** 构造函数 */
	UBTTask_RotateToFaceTarget();

	/** 从行为树资产初始化任务节点 */
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
	/** 获取任务节点所需的内存大小 */
	virtual uint16 GetInstanceMemorySize() const override;
	
	/** 获取节点的静态描述文本 */
	virtual FString GetStaticDescription() const override;

	/** 执行任务节点 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	/** 任务节点的周期性更新函数 */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** 
	 * 检查是否已达到目标旋转角度精度
	 * @param QueryPawn - 查询的AI角色
	 * @param TargetActor - 目标Actor
	 * @return bool - 是否已达到目标角度精度
	 */
	bool HasReachedAnglePrecision(APawn* QueryPawn, AActor* TargetActor) const;

	/** 目标旋转角度精度，控制旋转完成的判定标准 */
	UPROPERTY(EditAnywhere, Category="Face Target")
	float AnglePrecision;

	/** 旋转插值速度，控制旋转的平滑程度 */
	UPROPERTY(EditAnywhere, Category="Face Target")
	float RotationInterSpeed;

	/** 黑板中目标Actor的键选择器 */
	UPROPERTY(EditAnywhere, Category="Face Target")
	FBlackboardKeySelector InTargetToFaceKey;
};

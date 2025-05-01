// Jackie Lee .All Rights Reserved

#include "AI/BTTask_RotateToFaceTarget.h"
#include "AIController.h"
#include "KismetAnimationLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/KismetMathLibrary.h"

/**
 * 构造函数，初始化任务节点的基本属性
 * 设置节点名称、角度精度、旋转插值速度等参数
 */
UBTTask_RotateToFaceTarget::UBTTask_RotateToFaceTarget()
{
    // 设置节点名称
    NodeName = TEXT("Native Rotate to Face Target Actor");
    // 设置角度精度阈值，当与目标的角度差小于此值时认为已到达目标朝向
    AnglePrecision = 10.f;
    // 设置旋转插值速度，控制旋转的平滑程度
    RotationInterSpeed = 5.f;

    // 启用任务节点的Tick通知
    bNotifyTick = true;
    // 启用任务完成通知
    bNotifyTaskFinished = true;
    // 禁用节点实例创建
    bCreateNodeInstance = false;

    // 初始化任务节点通知标志
    INIT_TASK_NODE_NOTIFY_FLAGS();
    // 为黑板键选择器添加Actor类型过滤器
    InTargetToFaceKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetToFaceKey),
                                    AActor::StaticClass());
}

/**
 * 从行为树资产初始化任务节点
 * @param Asset - 所属的行为树资产
 */
void UBTTask_RotateToFaceTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);
    // 解析黑板键选择器
    if (UBlackboardData* BBAsset = GetBlackboardAsset())
    {
        InTargetToFaceKey.ResolveSelectedKey(*BBAsset);
    }
}

/**
 * 获取任务节点所需的内存大小
 * @return uint16 - 内存大小
 */
uint16 UBTTask_RotateToFaceTarget::GetInstanceMemorySize() const
{
    return sizeof(FRotateToFaceTargetTaskMemory);
}

/**
 * 获取节点的静态描述文本
 * @return FString - 描述该任务节点功能的文本
 */
FString UBTTask_RotateToFaceTarget::GetStaticDescription() const
{
    const FString KeyDescription = InTargetToFaceKey.SelectedKeyName.ToString();
    return FString::Printf(
        TEXT("Smoothly rotates to face %s Key until the angle precision %f"), *KeyDescription,
        *FString::SanitizeFloat(AnglePrecision));
}

/**
 * 执行任务节点
 * @param OwnerComp - 拥有该节点的行为树组件
 * @param NodeMemory - 节点内存
 * @return EBTNodeResult::Type - 任务执行结果
 */
EBTNodeResult::Type UBTTask_RotateToFaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // 从黑板中获取目标Actor
    UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetToFaceKey.SelectedKeyName);
    AActor* TargetActor = Cast<AActor>(ActorObject);

    // 获取AI控制的Pawn
    APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
    // 获取任务内存
    FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
    check(Memory);
    
    // 初始化内存数据
    Memory->OwningPawn = OwningPawn;
    Memory->TargetActor = TargetActor;
    
    // 检查数据有效性
    if (!Memory->IsValid())
    {
        return EBTNodeResult::Failed;
    }

    // 检查是否已达到目标朝向
    if (HasReachedAnglePrecision(OwningPawn, TargetActor))
    {
        Memory->Reset();
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::InProgress;
}

/**
 * 任务节点的周期性更新函数
 * @param OwnerComp - 拥有该节点的行为树组件
 * @param NodeMemory - 节点内存
 * @param DeltaSeconds - 帧间隔时间
 */
void UBTTask_RotateToFaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
    
    // 检查数据有效性
    if (Memory->IsValid())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }
    
    // 检查是否已达到目标朝向
    if (HasReachedAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
    {
        Memory->Reset();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
    else
    {
        // 计算朝向目标的旋转
        const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
            Memory->OwningPawn->GetActorLocation(), Memory->TargetActor->GetActorLocation());
        // 平滑插值到目标旋转
        const FRotator TargetRot = FMath::RInterpTo(Memory->OwningPawn->GetActorRotation(), LookAtRot, DeltaSeconds,
                                                RotationInterSpeed);
        // 应用旋转
        Memory->OwningPawn->SetActorRotation(TargetRot);
    }
}

/**
 * 检查是否已达到目标旋转角度精度
 * @param QueryPawn - 查询的AI角色
 * @param TargetActor - 目标Actor
 * @return bool - 是否已达到目标角度精度
 */
bool UBTTask_RotateToFaceTarget::HasReachedAnglePrecision(APawn* QueryPawn, AActor* TargetActor) const
{
    // 获取AI角色的前向向量
    const FVector OwnerForward = QueryPawn->GetActorForwardVector();
    // 获取AI角色到目标的归一化方向向量
    const FVector OwnerToTargetNormalized = (TargetActor->GetActorLocation() - QueryPawn->GetActorLocation()).
        GetSafeNormal();

    // 计算两个向量的点积
    const float DotResult = FVector::DotProduct(OwnerForward, OwnerToTargetNormalized);
    // 计算角度差
    const float AngleDiff = UKismetMathLibrary::DegAcos(DotResult);

    // 判断角度差是否在精度范围内
    return AngleDiff <= AnglePrecision;
}

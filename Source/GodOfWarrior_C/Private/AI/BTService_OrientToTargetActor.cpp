// Jackie Lee .All Rights Reserved

// 包含本类的头文件
#include "AI/BTService_OrientToTargetActor.h"

// 包含AI控制器相关头文件
#include "AIController.h"
// 包含黑板组件相关头文件
#include "BehaviorTree/BlackboardComponent.h"
// 包含黑板数据相关头文件
#include "BehaviorTree/BlackboardData.h"
// 包含数学库相关头文件
#include "Kismet/KismetMathLibrary.h"

/**
 * 构造函数
 * 初始化服务节点的基本属性和配置
 * 
 * 主要设置:
 * - 节点名称
 * - 服务节点通知标志
 * - 旋转插值速度默认值
 * - 更新间隔和随机偏差
 * - 目标Actor键的过滤器
 */
UBTService_OrientToTargetActor::UBTService_OrientToTargetActor()
{
    // 设置节点名称
    NodeName = TEXT("Native Orient Rotation To Target Actor");
    // 初始化服务节点的通知标志
    INIT_SERVICE_NODE_NOTIFY_FLAGS();

    // 设置默认的旋转插值速度
    RotationInterpSpeed = 5.f;
    // 设置更新间隔为0
    Interval = 0.f;
    // 设置随机偏差为0
    RandomDeviation = 0.f;

    // 为目标Actor键添加对象过滤器
    InTargetActorKey.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
}

/**
 * 从行为树资产初始化服务节点
 * 
 * @param Asset - 所属的行为树资产
 * 
 * 主要功能:
 * - 调用父类初始化
 * - 解析黑板中选定的目标Actor键
 */
void UBTService_OrientToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
    // 调用父类的初始化方法
    Super::InitializeFromAsset(Asset);
    // 获取黑板数据资产并解析选定的键
    if (UBlackboardData* BBAsset = GetBlackboardAsset())
    {
        InTargetActorKey.ResolveSelectedKey(*BBAsset);
    }
}

/**
 * 获取节点的静态描述文本
 * 
 * @return FString - 描述该服务节点功能的文本
 * 
 * 返回格式:
 * "Orient rotation to [键名] Key [服务描述]"
 */
FString UBTService_OrientToTargetActor::GetStaticDescription() const
{
    // 获取选定键的名称
    const FString KeyDescription = InTargetActorKey.SelectedKeyName.ToString();
    // 返回格式化的描述文本
    return FString::Printf(TEXT("Orient rotation to %s Key %s"), *KeyDescription, *GetStaticServiceDescription());
}

/**
 * 服务节点的周期性更新函数
 * 控制AI朝向目标Actor
 * 
 * @param OwnerComp - 拥有该节点的行为树组件
 * @param NodeMemory - 节点内存
 * @param DeltaSeconds - 帧间隔时间
 * 
 * 主要流程:
 * 1. 从黑板获取目标Actor
 * 2. 获取AI控制的Pawn
 * 3. 计算朝向目标的旋转值
 * 4. 使用插值平滑地更新Pawn的朝向
 */
void UBTService_OrientToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    // 调用父类的Tick方法
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // 从黑板中获取目标Actor对象
    UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);
    // 将对象转换为Actor类型
    AActor* TargetActor = Cast<AActor>(ActorObject);
    // 获取AI控制器所控制的Pawn
    APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

    // 如果拥有的Pawn和目标Actor都有效
    if (OwningPawn && TargetActor)
    {
        // 计算朝向目标的旋转值
        const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
            OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
        // 使用插值计算平滑的目标旋转值
        const FRotator TargetRot = FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRot, DeltaSeconds,
                                                RotationInterpSpeed);
        // 设置Pawn的旋转值   
        OwningPawn->SetActorRotation(TargetRot);
    }
}

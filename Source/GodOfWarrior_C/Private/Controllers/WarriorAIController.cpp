// Jackie Lee .All Rights Reserved

/**
 * WarriorAIController.cpp
 * AI控制器类的实现文件
 * 用于控制战士类型的AI角色
 * 
 * 主要功能:
 * - 管理AI战士的视觉感知系统
 * - 处理与其他角色的队伍关系判断
 * - 配置群体避让行为
 * - 响应感知事件并更新行为
 */

#include "Controllers/WarriorAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Debug/WarriorDebugHelper.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

/**
 * 构造函数
 * 初始化AI控制器并设置寻路组件
 * 
 * @param ObjectInitializer - 对象初始化器,用于设置默认子对象
 * 
 * 函数流程:
 * 1. 调用父类构造函数,设置CrowdFollowingComponent作为寻路组件
 * 2. 创建并配置视觉感知系统:
 *    - 设置只检测敌人,不检测友军和中立单位
 *    - 配置视觉范围、失去视野距离和视野角度
 * 3. 创建感知组件并设置视觉为主导感知
 * 4. 绑定感知更新事件处理函数
 * 5. 设置AI控制器的队伍ID
 * 
 * CrowdFollowingComponent功能:
 * - 实现群体寻路行为
 * - 处理AI角色之间的避让
 * - 优化多个AI同时寻路时的性能
 */
AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	// 创建并配置视觉感知配置
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySenseConfig_Sight");
	// 设置检测规则 - 只检测敌人,不检测友军和中立单位
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;

	// 配置视觉参数
	AISenseConfig_Sight->SightRadius = 5000.f; // 视觉范围半径
	AISenseConfig_Sight->LoseSightRadius = 0.f; // 失去视野的距离(0表示一旦超出视觉范围就立即失去目标)
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f; // 周边视觉角度(360度表示全方位视觉)

	// 创建感知组件并配置
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComponent");
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight); // 配置视觉感知
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass()); // 设置视觉为主导感知

	// 绑定感知更新事件
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	// 设置AI控制器的队伍ID
	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

/**
 * 获取对其他角色的态度
 * 实现自IGenericTeamAgentInterface接口
 * 
 * @param Other - 要检查态度的目标角色
 * @return ETeamAttitude::Type - 返回对目标的态度(敌对或友好)
 * 
 * 函数流程:
 * 1. 将目标转换为Pawn
 * 2. 获取目标的TeamAgent接口
 * 3. 比较双方的队伍ID:
 *    - 如果队伍ID不同,返回敌对态度(Hostile)
 *    - 如果队伍ID相同,返回友好态度(Friendly)
 */
ETeamAttitude::Type AWarriorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// 将输入的Actor转换为Pawn类型
	const APawn* PawnToCheck = Cast<const APawn>(&Other);

	// 获取目标Pawn的控制器并转换为TeamAgent接口
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(
		PawnToCheck->GetController());

	// 如果目标有TeamAgent接口且队伍ID小于自身队伍ID
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		// 返回敌对态度
		return ETeamAttitude::Hostile;
	}

	// 默认返回友好态度
	return ETeamAttitude::Friendly;
}

/**
 * 游戏开始时调用
 * 初始化AI控制器的运行时配置
 * 
 * 主要配置:
 * 1. 调用父类BeginPlay
 * 2. 获取并配置CrowdFollowingComponent:
 *    - 设置群体避让状态(启用/禁用)
 *    - 根据质量等级设置避让质量
 *    - 配置避让组和需要避让的组
 *    - 设置碰撞检测范围
 */
void AWarriorAIController::BeginPlay()
{
	Super::BeginPlay();

	// 获取并检查CrowdFollowingComponent是否有效
	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComp->SetCrowdSimulationState(bEnableDetourCrowAvoidance
			                                   ? ECrowdSimulationState::Enabled
			                                   : ECrowdSimulationState::Disabled);
		switch (DetourCrowAvoidanceQuality)
		{
		case 1: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		default:
			break;
		}
		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

/**
 * 感知更新事件处理函数
 * 当AI感知到目标状态发生变化时调用
 * 
 * @param Actor - 被感知到的角色
 * @param Stimulus - 感知刺激信息,包含感知类型和状态
 * 
 * 处理流程:
 * 1. 检查感知是否成功且目标Actor有效
 * 2. 获取黑板组件
 * 3. 将感知到的目标Actor设置到黑板的"TargetActor"键中
 */
void AWarriorAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    // 获取黑板组件
    if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
    {
        // 检查黑板中是否已有目标Actor
        if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
        {
            // 如果感知成功且目标Actor有效
            if (Stimulus.WasSuccessfullySensed() && Actor)
            {
                // 将感知到的Actor设置为目标
                BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
            }
        }
    }
}

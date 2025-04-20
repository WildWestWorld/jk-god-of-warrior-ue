// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WarriorAIController.generated.h"

class UAISenseConfig_Sight;

/**
 * 战士AI控制器类
 * 用于控制AI战士角色的行为
 * 包含视觉感知系统和队伍态度判断功能
 * 
 * 主要功能:
 * - 管理AI战士的视觉感知系统
 * - 处理与其他角色的队伍关系判断
 * - 配置群体避让行为
 * - 响应感知事件并更新行为
 */
UCLASS()
class GODOFWARRIOR_C_API AWarriorAIController : public AAIController
{
	GENERATED_BODY()

public:
	/**
	 * 构造函数
	 * 初始化AI控制器,设置寻路组件和感知系统
	 * 
	 * @param ObjectInitializer - 对象初始化器,用于配置默认子对象
	 * 
	 * 主要初始化内容:
	 * - 设置CrowdFollowingComponent作为寻路组件
	 * - 创建并配置视觉感知系统
	 * - 设置感知组件参数
	 * - 绑定感知更新事件
	 */
	AWarriorAIController(const FObjectInitializer& ObjectInitializer);

	/**
	 * 获取对其他角色的态度
	 * 实现自IGenericTeamAgentInterface接口
	 * 
	 * @param Other - 要判断态度的目标角色
	 * @return ETeamAttitude::Type - 返回对目标的态度(敌对或友好)
	 * 
	 * 判断逻辑:
	 * - 获取目标角色的队伍ID
	 * - 比较与自身队伍ID
	 * - 根据比较结果返回相应态度
	 */
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	/**
	 * 游戏开始时调用
	 * 初始化AI控制器的运行时配置
	 * 
	 * 主要配置:
	 * - 设置群体避让状态
	 * - 配置避让质量等级
	 * - 设置避让组和碰撞检测范围
	 */
	virtual void BeginPlay() override;

	/** 
	 * AI感知组件
	 * 用于处理AI的感知系统,如视觉感知等
	 * 
	 * 功能:
	 * - 管理AI的感知能力
	 * - 处理感知事件
	 * - 维护感知目标信息
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	/**
	 * 视觉感知配置
	 * 配置AI的视觉参数,如视野范围、角度等
	 * 
	 * 主要参数:
	 * - 视觉范围
	 * - 视野角度
	 * - 目标检测规则
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	/**
	 * 感知更新事件处理函数
	 * 当AI感知到目标状态变化时调用
	 * 
	 * @param Actor - 被感知到的角色
	 * @param Stimulus - 感知刺激信息,包含感知类型和状态
	 * 
	 * 处理流程:
	 * - 验证感知是否有效
	 * - 更新黑板中的目标信息
	 * - 触发相应的行为响应
	 */
	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	/** 是否启用Detour群体避让系统 */
	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config")
	bool bEnableDetourCrowAvoidance = true;

	/** 
	 * Detour群体避让质量等级(1-4)
	 * 1=低质量, 2=中等质量, 3=良好质量, 4=高质量
	 * 质量越高计算越精确,但性能消耗越大
	 */
	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config",
		meta=(EditCondition="bEnableDetourCrowAvoidance", UIMin="1", UIMax="4"))
	int32 DetourCrowAvoidanceQuality = 4;

	/** 
	 * 碰撞查询范围
	 * 定义AI进行避让计算时检查周围其他角色的范围
	 * 范围越大避让效果越好,但性能消耗越大
	 */
	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config",
		meta=(EditCondition="bEnableDetourCrowAvoidance"))
	float CollisionQueryRange = 600.f;
};

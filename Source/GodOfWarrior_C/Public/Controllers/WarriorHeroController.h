// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "WarriorHeroController.generated.h"

/**
 * 英雄角色控制器类
 * 用于控制玩家操控的英雄角色
 * 实现了队伍系统接口以支持敌我判断
 */
UCLASS()
class GODOFWARRIOR_C_API AWarriorHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	/**
	 * 构造函数
	 * 初始化英雄控制器,设置队伍ID
	 */
	AWarriorHeroController();

	/**
	 * 获取队伍ID
	 * 实现自IGenericTeamAgentInterface接口
	 * @return 返回英雄的队伍ID
	 */
	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	/** 
	 * 英雄的队伍ID
	 * 用于区分敌我,与AI进行交互
	 */
	FGenericTeamId HeroTeamID;
};

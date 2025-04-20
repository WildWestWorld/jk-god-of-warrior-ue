// Jackie Lee .All Rights Reserved

/**
 * WarriorHeroController.cpp
 * 英雄控制器类的实现文件
 * 用于控制玩家操控的英雄角色
 */

#include "Controllers/WarriorHeroController.h"

/**
 * 构造函数
 * 初始化英雄控制器并设置队伍ID
 * 
 * 函数流程:
 * 1. 设置英雄的队伍ID为0,表示玩家所在队伍
 */
AWarriorHeroController::AWarriorHeroController()
{
	HeroTeamID = FGenericTeamId(0);
}

/**
 * 获取队伍ID
 * 实现自IGenericTeamAgentInterface接口
 * 
 * @return FGenericTeamId - 返回英雄的队伍ID
 * 
 * 函数流程:
 * 1. 返回存储的英雄队伍ID
 */
FGenericTeamId AWarriorHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}

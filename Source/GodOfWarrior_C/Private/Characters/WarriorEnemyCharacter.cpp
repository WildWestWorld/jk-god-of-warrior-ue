// Jackie Lee .All Rights Reserved


#include "Characters/WarriorEnemyCharacter.h"

#include "Components/Pawn/Combat/EnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

/**
 * 敌人角色类的构造函数
 * 
 * 该构造函数设置了敌人角色的基本属性:
 * 1. AI控制相关设置 - 设置AI自动控制
 * 2. 旋转控制设置 - 禁用角色的各轴旋转
 * 3. 移动组件的相关参数 - 配置移动速度、旋转等
 */
AWarriorEnemyCharacter::AWarriorEnemyCharacter()
{
	// 设置AI自动控制 - 当角色被放置在世界中或生成时,会自动被AI控制器控制
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 禁用角色的Pitch(俯仰)、Roll(翻滚)和Yaw(偏航)旋转
	// 这样可以防止角色在移动时发生不必要的旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// 配置角色移动组件(CharacterMovementComponent)的参数
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();

	// 禁用控制器期望的旋转方向
	MovementComp->bUseControllerDesiredRotation = false;

	// 启用朝向移动方向的旋转 - 使角色始终面向移动方向
	MovementComp->bOrientRotationToMovement = true;

	// 设置旋转速率 - 每秒旋转180度,只在Yaw轴上旋转
	MovementComp->RotationRate = FRotator(0.f, 180.f, 0.f);

	// 设置最大行走速度为300单位/秒
	MovementComp->MaxWalkSpeed = 300.f;

	// 设置行走减速度为1000单位/秒² - 控制角色停止时的减速表现
	MovementComp->BrakingDecelerationWalking = 1000.f;


	// 创建并初始化敌人战斗组件
	// 该组件负责处理敌人的战斗相关功能,如攻击、受伤等
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
}

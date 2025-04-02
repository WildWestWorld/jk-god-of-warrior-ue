// Jackie Lee .All Rights Reserved


#include "Characters/WarriorEnemyCharacter.h"

#include "Components/Pawn/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Debug/WarriorDebugHelper.h"

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

UPawnCombatComponent* AWarriorEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent                             ;
}

/**
 * 当角色被控制器占有时调用
 * 重写自父类的虚函数
 * 用于在AI控制器开始控制该敌人角色时进行初始化设置
 * 
 * @param NewController - 接管控制的新控制器实例
 */
void AWarriorEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
}

/**
 * 初始化敌人的启动数据
 * 该函数异步加载并应用敌人角色的初始化数据
 * 
 * 函数流程:
 * 1. 检查CharacterStartUpData是否为空
 * 2. 使用异步加载管理器加载数据资产
 * 3. 加载完成后将数据应用到能力系统组件
 * 4. 打印调试信息确认加载完成
 */
void AWarriorEnemyCharacter::InitEnemyStartUpData()
{
	// 检查启动数据是否为空,如果为空则直接返回
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	// 使用资产管理器获取流式管理器,请求异步加载启动数据
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		// 将软对象引用转换为路径用于加载
		CharacterStartUpData.ToSoftObjectPath(),
		// 创建一个Lambda表达式作为加载完成后的回调
		FStreamableDelegate::CreateLambda([this]()
		{
			// 尝试获取加载完成的数据资产
			if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
			{
				// 将加载的数据应用到角色的能力系统组件
				LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
				// 打印调试信息表示数据加载成功
				Debug::Print(TEXT("Enemy Start Up Data Loaded"), FColor::Green);
			}
		})
	);
}

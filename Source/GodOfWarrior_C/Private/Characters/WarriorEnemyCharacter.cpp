// Jackie Lee .All Rights Reserved


#include "Characters/WarriorEnemyCharacter.h"

#include "Components/WidgetComponent.h"
#include "Components/Pawn/Combat/EnemyCombatComponent.h"
#include "Components/Pawn/UI/Enemy/EnemyUIComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Debug/WarriorDebugHelper.h"
#include "Widgets/WarriorWidgetBase.h"

/**
 * 敌人角色类的构造函数
 * 初始化敌人角色的基本属性和组件
 */
AWarriorEnemyCharacter::AWarriorEnemyCharacter()
{
	// 设置AI自动控制 - 当角色被放置在世界中或生成时会自动被AI控制器控制
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 禁用角色的各轴旋转,防止不必要的旋转
	bUseControllerRotationPitch = false; // 禁用俯仰旋转
	bUseControllerRotationRoll = false; // 禁用翻滚旋转
	bUseControllerRotationYaw = false; // 禁用偏航旋转

	// 获取并配置角色移动组件
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();

	// 禁用控制器期望的旋转方向
	MovementComp->bUseControllerDesiredRotation = false;

	// 启用朝向移动方向的旋转,使角色始终面向移动方向
	MovementComp->bOrientRotationToMovement = true;

	// 设置旋转速率 - 每秒在Yaw轴上旋转180度
	MovementComp->RotationRate = FRotator(0.f, 180.f, 0.f);

	// 设置最大行走速度(单位:虚幻单位/秒)
	MovementComp->MaxWalkSpeed = 300.f;

	// 设置行走减速度,控制角色停止时的减速效果
	MovementComp->BrakingDecelerationWalking = 1000.f;

	// 创建并初始化战斗组件 - 处理攻击、受伤等战斗相关功能
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");

	// 创建并初始化UI组件 - 处理敌人相关的UI显示
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>("EnemyUIComponent");

	// 创建并初始化血条Widget组件
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComponent");

	// 将血条Widget组件附加到角色的骨骼网格体上
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

UPawnCombatComponent* AWarriorEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AWarriorEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AWarriorEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
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
 * 游戏开始时调用的函数
 * 重写自父类的虚函数
 * 用于初始化敌人角色的UI界面
 * 
 * 函数流程:
 * 1. 调用父类的BeginPlay
 * 2. 获取敌人血条Widget组件
 * 3. 初始化血条Widget的显示
 */
void AWarriorEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (UWarriorWidgetBase* HealthWidget = Cast<UWarriorWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
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
			}
		})
	);
}

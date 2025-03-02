// Jackie Lee .All Rights Reserved

#include "Characters/WarriorHeroCharacter.h"

// 添加调试器
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/Input/WarriorEnhancedInputComponent.h"
#include "Components/Pawn/Combat/HeroCombatComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "Debug/WarriorDebugHelper.h"
#include "GameplayTags/WarriorGameplayTags.h"

// init
AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	// 初始化胶囊
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	// 禁用原生鼠标控制
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 创建弹簧臂
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// 添加弹簧臂(GetRootComponent:根节点)
	CameraBoom->SetupAttachment(GetRootComponent());
	// 设置弹簧臂的长度
	CameraBoom->TargetArmLength = 200.f;
	// CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f); 的作用是调整相机的位置偏移，使相机相对于 SpringArm（即角色的背后）稍微向右偏移 55 单位，向上偏移 65 单位。
	// 这使得相机在游戏中能更好地跟随角色，并保持理想的视角。
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	// 设置 CameraBoom（Spring Arm）使用角色控制器的旋转。
	// 这使得 Spring Arm 的方向会随着角色的旋转而变化，通常用于第三人称相机视角。
	// 如果设置为 true，相机会随着角色的旋转而旋转，从而始终跟随角色的朝向。
	// 如果设置为 false，相机的位置和旋转会由其他因素（如物理或动画）控制，而不直接依赖于角色的旋转。
	// 让弹簧臂旋转，相机会随着弹簧臂旋转
	CameraBoom->bUsePawnControlRotation = true;

	// 创建相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// 附着到相机上
	//  SocketName 用来标识 CameraBoom 上的默认插槽，确保摄像机在该位置附加并跟随弹簧臂的运动。
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// 让弹簧臂旋转，相机会随着弹簧臂旋转,相机不旋转
	FollowCamera->bUsePawnControlRotation = false;

	// 设置角色朝向移动方向 - 当角色移动时，会自动旋转面向移动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 设置角色旋转速率 - FRotator(Pitch俯仰角, Yaw偏航角, Roll翻滚角)，这里设置每秒旋转500度
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	// 设置角色最大行走速度为400m/秒
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	// 设置角色行走时的制动减速度为2000m/秒，影响角色停止移动时的减速效果
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// 创建Combat组件
	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
}

// 开始的生命周期
void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Debug 命名空间
	// Print调用 命名空间的打印函数
	Debug::Print(TEXT("Working"));
}

// 生命周期
// A[Actor 创建] --> B[构造函数]
// B --> C[SetupPlayerInputComponent]
// C --> D[BeginPlay]
// D --> E[正常游戏循环]

// 初始化Input组件
// 不要使用InputComponent 作为变量名
/**
 * 设置玩家输入组件，配置增强输入系统
 * @param PlayerInputComponent - 输入组件指针
 */
// SetupPlayerInputComponent 和 BeginPlay 一样会自己运行
// UInputComponent* PlayerInputComponent 是函数返回值 e
void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 确保输入配置数据资产已设置,InputConfigDataAsset 是在编辑器里面我们设置的，里面放着DefaultMap
	checkf(InputConfigDataAsset, TEXT("Forget to assign a valid data asset as input config"))

	//---- 这里是为了设置 MappingContext
	// 获取本地玩家
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	// 获取增强输入子系统，拿子系统是为了放MappingContext
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	// 确保子系统存在
	check(Subsystem);
	// 添加默认输入映射上下文
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	//-----

	// UWarriorEnhancedInputComponent 使我们自定义的类
	// 转换为增强输入组件
	// 为什么能转化？因为UWarriorEnhancedInputComponent 创建的时候就继承自UWarriorEnhancedInputComponent
	UWarriorEnhancedInputComponent* WarriorEnhancedInputComponent = CastChecked<UWarriorEnhancedInputComponent>(
		PlayerInputComponent);

	// EnhanceInput绑定移动输入动作
	// 不使用，移动不了人物
	WarriorEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Move,
	                                                     ETriggerEvent::Triggered, this, &ThisClass::Input_Move);

	// EnhanceInput绑定观察/鼠标移动动作
	// 不使用，移动不了镜头
	WarriorEnhancedInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Look,
	                                                     ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	// 绑定技能输入动作
	// @param InputConfigDataAsset - 包含输入配置的数据资产
	// @param this - 当前角色实例
	// @param Input_AbilityInputPressed - 按下输入时调用的回调函数
	// @param Input_AbilityInputReleased - 释放输入时调用的回调函数
	//BindAbilityInputAction 是哦们自己写的事件
	WarriorEnhancedInputComponent->BindAbilityInputAction(InputConfigDataAsset, this,
	                                                      &ThisClass::Input_AbilityInputPressed,
	                                                      &ThisClass::Input_AbilityInputReleased);
}

// 生命周期
/**
 * 当角色被Controller控制时调用此函数
 * @param NewController 接管控制的Controller指针
 */
void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	// 调用父类的PossessedBy方法
	Super::PossessedBy(NewController);
	// 检查角色升星数据是否存在/有效
	if (!CharacterStartUpData.IsNull())
	{
		// 尝试同步加载数据资源
		// UDataAsset_StartUpDataBase* 是一个自定义的数据资源类
		// LoadSynchronous() 会阻塞当前线程直到加载完成
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			// 将加载的数据应用到角色的技能系统组件中
			// 这可能包含了角色升星后获得的新技能、属性加成等数据
			LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
		}
	}
}

/**
 * 处理角色移动输入的函数
 * @param InputActionValue - 包含移动输入数据的结构体，来自增强输入系统,是事件返回的值类似于 js里面的Event事件
 */
void AWarriorHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	// 从输入动作值中获取2D移动向量
	// MovementVector.X 代表左右移动输入值 (-1.0 = 左, 1.0 = 右)
	// MovementVector.Y 代表前后移动输入值 (-1.0 = 后, 1.0 = 前)
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	// 创建一个只包含偏航角(Yaw)的旋转器
	// 通过获取控制器的当前旋转，确保移动方向跟随摄像机朝向
	// 仅使用Yaw分量以保持角色保持直立（不考虑Pitch和Roll）
	const FRotator MovementRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);

	// 处理前后移动
	if (MovementVector.Y != 0.f) // 检查是否有前后方向的输入
	{
		// 将世界空间的前向单位向量(1,0,0)根据当前视角进行旋转
		// 这样可以确保"前进"永远是相对于摄像机的前方，而不是角色模型的朝向
		//
		// 		FVector::ForwardVector 是虚幻引擎中的一个静态常量向量，表示世界坐标系中的前向单位向量，其值为 (1, 0, 0)。在 3D 空间中：
		// X 轴 (1,0,0) 代表前向
		// Y 轴 (0,1,0) 代表右向
		// Z 轴 (0,0,1) 代表上向
		const FVector ForwardDirection = MovementRotator.RotateVector(FVector::ForwardVector);

		// 调用父类的移动输入函数，将旋转后的方向向量与输入值相乘
		// MovementVector.Y作为输入强度，决定移动速度的比例
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	// 处理左右移动
	if (MovementVector.X != 0.f) // 检查是否有左右方向的输入
	{
		// 将世界空间的右向单位向量(0,1,0)根据当前视角进行旋转
		// 这样可以确保"右移"永远是相对于摄像机的右方，而不是角色模型的右方
		const FVector RightDirection = MovementRotator.RotateVector(FVector::RightVector);

		// 调用父类的移动输入函数，将旋转后的方向向量与输入值相乘
		// MovementVector.X作为输入强度，决定移动速度的比例
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWarriorHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	// 从输入值中获取二维向量，表示鼠标/摇杆的移动方向和强度
	// X: 水平方向的输入值（左右移动）
	// Y: 垂直方向的输入值（上下移动）
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	// 处理水平方向的视角旋转（左右转向）
	if (LookAxisVector.X != 0.f)
	{
		// AddControllerYawInput: 添加水平旋转输入
		// Yaw: 表示角色的水平旋转角度（绕垂直轴旋转）
		// LookAxisVector.X: 正值表示向右转，负值表示向左转
		AddControllerYawInput(LookAxisVector.X);
	}

	// 处理垂直方向的视角旋转（上下看）
	if (LookAxisVector.Y != 0.f)
	{
		// AddControllerPitchInput: 添加垂直旋转输入
		// Pitch: 表示摄像机的垂直旋转角度（抬头/低头）
		// LookAxisVector.Y: 正值表示向上看，负值表示向下看
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

/**
 * 处理技能输入按下事件的函数
 * 当玩家按下技能按键时调用此函数
 * @param InputTag - 与按下输入关联的游戏标签，用于识别具体是哪个技能输入
 */
void AWarriorHeroCharacter::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	WarriorAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

/**
 * 处理技能输入释放事件的函数
 * 当玩家释放技能按键时调用此函数
 * @param InputTag - 与释放输入关联的游戏标签，用于识别具体是哪个技能输入
 */
void AWarriorHeroCharacter::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	WarriorAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}

// Jackie Lee .All Rights Reserved


#include "Characters/WarriorHeroCharacter.h"

// 添加调试器
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Debug/WarriorDebugHelper.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// init
AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	// 初始化胶囊
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	//禁用原生鼠标控制
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//创建弹簧臂
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//添加弹簧臂(GetRootComponent:根节点)
	CameraBoom->SetupAttachment(GetRootComponent());
	//设置弹簧臂的长度
	CameraBoom->TargetArmLength = 200.f;
	// CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f); 的作用是调整相机的位置偏移，使相机相对于 SpringArm（即角色的背后）稍微向右偏移 55 单位，向上偏移 65 单位。
	// 这使得相机在游戏中能更好地跟随角色，并保持理想的视角。
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	// 设置 CameraBoom（Spring Arm）使用角色控制器的旋转。
	// 这使得 Spring Arm 的方向会随着角色的旋转而变化，通常用于第三人称相机视角。
	// 如果设置为 true，相机会随着角色的旋转而旋转，从而始终跟随角色的朝向。
	// 如果设置为 false，相机的位置和旋转会由其他因素（如物理或动画）控制，而不直接依赖于角色的旋转。
	//让弹簧臂旋转，相机会随着弹簧臂旋转
	CameraBoom->bUsePawnControlRotation = true;

	//创建相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//附着到相机上
	// SocketName 用来标识 CameraBoom 上的默认插槽，确保摄像机在该位置附加并跟随弹簧臂的运动。
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//让弹簧臂旋转，相机会随着弹簧臂旋转,相机不旋转
	FollowCamera->bUsePawnControlRotation = false;

	// 设置角色朝向移动方向 - 当角色移动时，会自动旋转面向移动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 设置角色旋转速率 - FRotator(Pitch俯仰角, Yaw偏航角, Roll翻滚角)，这里设置每秒旋转500度
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	// 设置角色最大行走速度为400m/秒
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	// 设置角色行走时的制动减速度为2000m/秒，影响角色停止移动时的减速效果
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Debug 命名空间
	//Print调用 命名空间的打印函数
	Debug::Print(TEXT("Working"));
}

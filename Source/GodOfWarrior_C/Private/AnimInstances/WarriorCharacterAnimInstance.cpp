// Jackie Lee .All Rights Reserved


#include "AnimInstances/WarriorCharacterAnimInstance.h"

#include "Characters/WarriorBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//----- 设置 OwningCharacter 变量
	// AWarriorBaseCharacter 继承自 ACharacter， ACharacter 继承自 AActor,AActor 继承自 APawn ，所以TryGetPawnOwner可以转为AWarriorBaseCharacter 
	APawn* OwningPawn = TryGetPawnOwner();
	OwningCharacter = Cast<AWarriorBaseCharacter>(OwningPawn);
	//-----
	//如果可以正常转化的话，就获取 到CharacterMovement 组件 ，设置 OwningMovementComponent 变量
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	//如果没有Character(Pawn)/Movement组件 就不要执行
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	// 获取角色在XY平面(地面)上的移动速度(单位:UU/s)
	// Size2D()计算二维向量的长度: √(X² + Y²)
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	// 获取当前加速度向量在XY平面上长度的平方
	// SizeSquared2D()计算二维向量长度的平方: X² + Y²
	// 使用平方值可以避免开平方运算,提高性能
	// 通常用于需要比较加速度大小而不需要具体数值的场景
	//就是看有没有加速度
	IsHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	
}

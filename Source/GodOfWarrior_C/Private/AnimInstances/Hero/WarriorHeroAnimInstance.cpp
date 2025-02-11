// Jackie Lee .All Rights Reserved


#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"

#include "Characters/WarriorHeroCharacter.h"

void UWarriorHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//OwningCharacter 来自于父级 UWarriorCharacterAnimInstance 在 init生命周期赋值
	if (OwningCharacter)
	{
		//将OwningCharacter 转化为 AWarriorHeroCharacter 
		// 为什么可以转化?AWarriorHeroCharacter 使我们自定义的角色基类 继承自 AWarriorBaseCharacter
		OwningHeroCharacter = Cast<AWarriorHeroCharacter>(OwningCharacter);
	}
}

void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	//如果有加速度就重置Idle时间，以及进入Relax的状态，没有就计算Idle时间，时间到了 就改变Relax 状态的过渡条件
	if (IsHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		IsShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime = IdleElapsedTime + DeltaSeconds;
		if (IdleElapsedTime >= EnterRelaxStateThresholdTime)
		{
			IsShouldEnterRelaxState = true;
		}
		else
		{
			IsShouldEnterRelaxState = false;
		}
	}
}

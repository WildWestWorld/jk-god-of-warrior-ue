// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "WarriorHeroAnimInstance.generated.h"

class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorHeroAnimInstance : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()

public:
	//生命周期 初始化动画
	virtual void NativeInitializeAnimation() override;
	//Lyra开始的生命周期
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	// VisibleDefaultsOnly: 在编辑器 只能查看,不能编辑
	// EditDefaultsOnly:  在编辑器  可以查看也可以编辑


	// AWarriorHeroCharacter 使我们自定义的角色基类 继承自 AWarriorBaseCharacter
	//用于获取英雄角色的实例，AWarriorBaseCharacter = 泛化  AWarriorHeroCharacter = 具体，就是获取Hero角色的具体信息
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|References")
	AWarriorHeroCharacter* OwningHeroCharacter;

	//是否进入Relax 状态
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool IsShouldEnterRelaxState;

	//进入Relax事件门槛时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float EnterRelaxStateThresholdTime = 5.f;

	//记录角色不动/Idle的时间
	float IdleElapsedTime = 0.f;
};

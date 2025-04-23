// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "WarriorCharacterAnimInstance.generated.h"


class UCharacterMovementComponent;
class AWarriorBaseCharacter;
/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorCharacterAnimInstance : public UWarriorBaseAnimInstance
{
	GENERATED_BODY()

public:
	//生命周期 初始化动画
	virtual void NativeInitializeAnimation() override;
	//Lyra开始的生命周期
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	// AWarriorBaseCharacter 使我们自定义的角色基类
	UPROPERTY()
	AWarriorBaseCharacter* OwningCharacter;
	//移动组件，每个Character都会有的
	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;
	//地面的移动速度
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float GroundSpeed;
	//是否有加速度
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool IsHasAcceleration;

	//移动方向
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float LocomotionDirection;
};

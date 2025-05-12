// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

class UInputMappingContext;
class UWarriorWidgetBase;
/**
 * 目标锁定技能类
 * 用于实现角色的目标锁定功能,可以锁定范围内的敌人
 * 通过盒体追踪检测范围内的可锁定目标,并自动选择最近的目标进行锁定
 * 支持显示目标锁定UI,方便玩家识别当前锁定的目标
 */
UCLASS()
class GODOFWARRIOR_C_API UHeroGameplayAbility_TargetLock : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	/**
	 * 激活目标锁定技能
	 * 当技能被激活时调用,用于初始化目标锁定功能
	 * @param Handle - 技能规格句柄
	 * @param ActorInfo - 技能执行者信息
	 * @param ActivationInfo - 技能激活信息
	 * @param TriggerEventData - 触发事件数据
	 */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	/**
	 * 结束目标锁定技能
	 * 当技能结束时调用,用于清理目标锁定状态
	 * @param Handle - 技能规格句柄
	 * @param ActorInfo - 技能执行者信息
	 * @param ActivationInfo - 技能激活信息
	 * @param bReplicateEndAbility - 是否复制结束技能
	 * @param bWasCancelled - 是否被取消
	 */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;


	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);

private:
	/**
	 * 尝试锁定目标
	 * 在可用目标中选择并锁定一个目标
	 * 如果没有可用目标或无法锁定目标,则取消技能
	 */
	void TryLockTarget();

	/**
	 * 获取可锁定的目标列表
	 * 使用盒体追踪检测范围内的可锁定目标
	 * 将检测到的目标添加到可用目标列表中
	 */
	void GetAvailableActorsToLock();

	/**
	 * 从可用目标列表中选择最近的目标
	 * @param InAvailableActors - 可用目标列表
	 * @return 返回最近的目标Actor,如果没有可用目标则返回nullptr
	 */
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);

	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);

	/**
	 * 绘制目标锁定UI
	 * 创建并显示目标锁定UI组件
	 * 如果UI组件已存在则不会重复创建
	 */
	void DrawTargetLockWidget();

	void SetTargetLockWidgetPosition();

	void InitTargetLockMovement();

	void InitTargetLockMappingContext();

	/**
	 * 取消目标锁定技能
	 * 调用父类的CancelAbility方法取消技能
	 */
	void CancelTargetLockAbility();

	/**
	 * 清理目标锁定状态
	 * 清空可用目标列表
	 * 清除当前锁定目标
	 * 移除目标锁定UI
	 */
	void CleanUp();

	void ResetTargetLockMovement();
	void ResetTargetLockMappingContext();

	/** 盒体追踪的距离,用于确定目标检测范围 */
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float BoxTraceDistance = 5000.f;

	/** 盒体追踪的大小,用于确定目标检测区域 */
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	FVector TraceBoxSize = FVector(5000.f, 5000.f, 300.f);

	/** 盒体追踪的通道类型,用于确定可锁定的目标类型 */
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;

	/** 是否显示持久化的调试形状,用于调试目标检测范围 */
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	bool bShowPersistentDebugShape = false;

	/** 目标锁定UI的类,用于创建目标锁定UI组件 */
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TSubclassOf<UWarriorWidgetBase> TargetLockWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockRotationInterpSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockMaxWalkSpeed = 150.f;
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	UInputMappingContext* TargetLockMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockCameraOffsetDistance = 20.f;

	/** 可锁定的目标列表,存储检测到的可锁定目标 */
	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	/** 当前锁定的目标Actor */
	UPROPERTY()
	AActor* CurrentLockedActor;

	/** 目标锁定UI组件实例 */
	UPROPERTY()
	UWarriorWidgetBase* DrawnTargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

	UPROPERTY()
	float CachedDefaultMaxWalkSpeed = 0.f;
};

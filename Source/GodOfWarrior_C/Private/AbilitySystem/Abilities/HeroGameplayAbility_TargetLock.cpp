// Jackie Lee .All Rights Reserved

#include "AbilitySystem/Abilities/HeroGameplayAbility_TargetLock.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "BlueprintFunctionLibrary/WarriorBlueprintFunctionLibrary.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Components/SizeBox.h"
#include "Debug/WarriorDebugHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/WarriorWidgetBase.h"
#include "Controllers/WarriorHeroController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTags/WarriorGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"

/**
 * 激活目标锁定技能
 * 当技能被激活时调用,用于初始化目标锁定功能
 * @param Handle - 技能规格句柄
 * @param ActorInfo - 技能执行者信息
 * @param ActivationInfo - 技能激活信息
 * @param TriggerEventData - 触发事件数据
 */
void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                      const FGameplayAbilityActorInfo* ActorInfo,
                                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	TryLockTarget();
	InitTargetLockMovement();
	InitTargetLockMappingContext();
}

/**
 * 结束目标锁定技能
 * 当技能结束时调用,用于清理目标锁定状态
 * @param Handle - 技能规格句柄
 * @param ActorInfo - 技能执行者信息
 * @param ActivationInfo - 技能激活信息
 * @param bReplicateEndAbility - 是否复制结束技能
 * @param bWasCancelled - 是否被取消
 */
void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
	CleanUp();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor ||
		UWarriorBlueprintFunctionLibrary::NativeIsActorHasTag(CurrentLockedActor,
		                                                      WarriorGameplayTags::Shared_Status_Dead) ||
		UWarriorBlueprintFunctionLibrary::NativeIsActorHasTag(GetHeroCharacterFromActorInfo(),
		                                                      WarriorGameplayTags::Shared_Status_Dead))
	{
		CancelTargetLockAbility();
		return;
	}

	SetTargetLockWidgetPosition();

	const bool bShouldOverrideRotation =
		!UWarriorBlueprintFunctionLibrary::NativeIsActorHasTag(GetHeroCharacterFromActorInfo(),
		                                                       WarriorGameplayTags::Player_Status_Rolling) && !
		UWarriorBlueprintFunctionLibrary::NativeIsActorHasTag(GetHeroCharacterFromActorInfo(),
		                                                      WarriorGameplayTags::Player_Status_Blocking);
	if (bShouldOverrideRotation)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
			GetHeroCharacterFromActorInfo()->GetActorLocation(), CurrentLockedActor->GetActorLocation());

		LookAtRot = LookAtRot - FRotator(TargetLockCameraOffsetDistance, 0.f, 0.f);

		const FRotator CurrentControlRot = GetHeroCharacterFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime,
		                                            TargetLockRotationInterpSpeed);
		GetHeroControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		GetHeroCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}
}

void UHeroGameplayAbility_TargetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();

	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewTargetToLock = nullptr;

	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);
	if (InSwitchDirectionTag == WarriorGameplayTags::Player_Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}

	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

/**
 * 尝试锁定目标
 * 在可用目标中选择并锁定一个目标
 * 如果没有可用目标或无法锁定目标,则取消技能
 */
void UHeroGameplayAbility_TargetLock::TryLockTarget()
{
	GetAvailableActorsToLock();
	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);
	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}
}

/**
 * 获取可锁定的目标列表
 * 使用盒体追踪检测范围内的可锁定目标
 * 将检测到的目标添加到可用目标列表中
 * 使用BoxTraceMultiForObjects进行盒体追踪检测
 */
void UHeroGameplayAbility_TargetLock::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();

	// 存储盒体追踪的碰撞结果
	TArray<FHitResult> BoxTraceHits;

	// 执行盒体追踪检测
	// 参数说明:
	// - WorldContextObject: 使用英雄角色作为世界上下文对象
	// - Start: 从英雄当前位置开始追踪
	// - End: 在英雄前方BoxTraceDistance距离处结束追踪
	// - HalfSize: 使用TraceBoxSize的一半作为盒体大小
	// - Orientation: 使用英雄的前向向量作为盒体方向
	// - ObjectTypes: 使用配置的BoxTraceChannel作为检测通道
	// - bTraceComplex: 设置为false,使用简单碰撞检测
	// - ActorsToIgnore: 不忽略任何Actor
	// - DrawDebugType: 根据bShowPersistentDebugShape决定是否显示持久化调试形状
	// - OutHits: 存储检测到的碰撞结果
	// - bIgnoreSelf: 设置为true,忽略自身碰撞

	UKismetSystemLibrary::BoxTraceMultiForObjects(GetHeroCharacterFromActorInfo(),
	                                              GetHeroCharacterFromActorInfo()->GetActorLocation(),
	                                              GetHeroCharacterFromActorInfo()->GetActorLocation() +
	                                              GetHeroCharacterFromActorInfo()->GetActorForwardVector() *
	                                              BoxTraceDistance, TraceBoxSize / 2.f,
	                                              GetHeroCharacterFromActorInfo()->GetActorForwardVector().
	                                              ToOrientationRotator(), BoxTraceChannel, false, TArray<AActor*>(),
	                                              bShowPersistentDebugShape
		                                              ? EDrawDebugTrace::Persistent
		                                              : EDrawDebugTrace::None, BoxTraceHits, true);

	// 遍历所有碰撞结果
	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			// 确保不会锁定自己
			if (HitActor != GetHeroCharacterFromActorInfo())
			{
				// 将目标添加到可用目标列表中
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

/**
 * 从可用目标列表中选择最近的目标
 * @param InAvailableActors - 可用目标列表
 * @return 返回最近的目标Actor,如果没有可用目标则返回nullptr
 */
AActor* UHeroGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(), InAvailableActors,
	                                          ClosestDistance);
}

void UHeroGameplayAbility_TargetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft,
                                                                     TArray<AActor*>& OutActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	const FVector PlayerLocation = GetHeroCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
	for (AActor* AvailableActor : AvailableActorsToLock)
	{
		if (!AvailableActor || AvailableActor == CurrentLockedActor) continue;
		const FVector PlayerToAvailableNormalized = (AvailableActor->GetActorLocation() - PlayerLocation).
			GetSafeNormal();
		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentNormalized, PlayerToAvailableNormalized);

		if (CrossResult.Z > 0.f)
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}
	}
}

/**
 * 绘制目标锁定UI
 * 创建并显示目标锁定UI组件
 * 如果UI组件已存在则不会重复创建
 */
void UHeroGameplayAbility_TargetLock::DrawTargetLockWidget()
{
	if (!DrawnTargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forget to assign a valid widget class in BluePrint"));
		//使用  GetHeroControllerFromActorInfo 得引入 #include "Controllers/WarriorHeroController.h"
		DrawnTargetLockWidget = CreateWidget<UWarriorWidgetBase>(GetHeroControllerFromActorInfo(),
		                                                         TargetLockWidgetClass);
		check(DrawnTargetLockWidget);
		DrawnTargetLockWidget->AddToViewport();
	}
}

void UHeroGameplayAbility_TargetLock::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}
	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetHeroControllerFromActorInfo(), CurrentLockedActor->GetActorLocation(),
		ScreenPosition, true);


	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		DrawnTargetLockWidget->WidgetTree->ForEachWidget([this](UWidget* FoundWidget)
		{
			if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
			{
				TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
				TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
			}
		});
	}

	ScreenPosition -= (TargetLockWidgetSize / 2.f);
	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UHeroGameplayAbility_TargetLock::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed = GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void UHeroGameplayAbility_TargetLock::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(TargetLockMappingContext, 3);
}

/**
 * 取消目标锁定技能
 * 调用父类的CancelAbility方法取消技能
 */
void UHeroGameplayAbility_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

/**
 * 清理目标锁定状态
 * 清空可用目标列表
 * 清除当前锁定目标
 * 移除目标锁定UI
 */
void UHeroGameplayAbility_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();
	CurrentLockedActor = nullptr;
	if (DrawnTargetLockWidget)
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}
	DrawnTargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
	CachedDefaultMaxWalkSpeed = 0.f;
}

void UHeroGameplayAbility_TargetLock::ResetTargetLockMovement()
{
	if (CachedDefaultMaxWalkSpeed > 0.f)
	{
		GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
	}
}

void UHeroGameplayAbility_TargetLock::ResetTargetLockMappingContext()
{
	if (!GetHeroControllerFromActorInfo())
	{
		return;
	}

	const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->RemoveMappingContext(TargetLockMappingContext);
}

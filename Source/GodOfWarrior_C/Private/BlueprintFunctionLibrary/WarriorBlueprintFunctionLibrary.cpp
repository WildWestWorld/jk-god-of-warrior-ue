// Jackie Lee .All Rights Reserved


#include "BlueprintFunctionLibrary/WarriorBlueprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Debug/WarriorDebugHelper.h"
#include "GameplayTags/WarriorGameplayTags.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"

/**
 * 从Actor获取WarriorAbilitySystemComponent组件
 * 
 * @param InActor - 要获取组件的Actor对象
 * @return 返回转换后的WarriorAbilitySystemComponent组件指针
 * 
 * 该函数首先检查输入的Actor是否有效，然后:
 * 1. 使用UAbilitySystemBlueprintLibrary获取Actor上的AbilitySystemComponent
 * 2. 将获取到的组件转换为WarriorAbilitySystemComponent类型
 * 3. 如果转换失败则返回nullptr
 */
UWarriorAbilitySystemComponent* UWarriorBlueprintFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
	// 检查传入的Actor指针是否有效
	check(InActor)

	// 获取Actor上的AbilitySystemComponent并转换为WarriorAbilitySystemComponent类型
	// 如果转换失败会自动返回nullptr
	return Cast<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

/**
 * 为Actor添加GameplayTag（如果不存在）
 * 
 * @param InActor - 目标Actor
 * @param TagToAdd - 要添加的GameplayTag
 * 
 * 该函数会:
 * 1. 获取Actor的能力系统组件
 * 2. 检查是否已有指定标签
 * 3. 如果没有该标签，则添加它
 */
void UWarriorBlueprintFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	// 获取Actor的能力系统组件
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	// 如果Actor没有指定的标签，则添加它
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

/**
 * 从Actor移除GameplayTag（如果存在）
 * 
 * @param InActor - 目标Actor
 * @param TagToRemove - 要移除的GameplayTag
 * 
 * 该函数会:
 * 1. 获取Actor的能力系统组件
 * 2. 检查是否有指定标签
 * 3. 如果有该标签，则移除它
 */
void UWarriorBlueprintFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	// 获取Actor的能力系统组件
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	// 如果Actor有指定的标签，则移除它
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

/**
 * 检查Actor是否拥有指定的GameplayTag
 * 
 * @param InActor - 要检查的目标Actor
 * @param TagToCheck - 要检查的GameplayTag
 * @return 如果Actor拥有指定标签返回true，否则返回false
 * 
 * 该函数会:
 * 1. 获取Actor的能力系统组件
 * 2. 检查是否有指定标签
 * 3. 返回检查结果
 */
bool UWarriorBlueprintFunctionLibrary::NativeIsActorHasTag(AActor* InActor, FGameplayTag TagToCheck)
{
	// 获取Actor的能力系统组件并检查是否有指定标签
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

/**
 * 蓝图版本的Actor标签检查函数
 * 
 * @param InActor - 要检查的目标Actor
 * @param TagToCheck - 要检查的GameplayTag
 * @param OutConfirmType - 输出参数，表示检查结果(Yes/No)
 * 
 * 该函数是NativeIsActorHasTag的蓝图版本:
 * 1. 调用原生检查函数
 * 2. 将bool结果转换为枚举类型
 * 3. 通过引用参数返回结果
 */
void UWarriorBlueprintFunctionLibrary::BP_IsActorHasTag(AActor* InActor, FGameplayTag TagToCheck,
                                                        EWarriorConfirmType& OutConfirmType)
{
	// 根据标签检查结果设置确认类型
	OutConfirmType = NativeIsActorHasTag(InActor, TagToCheck) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
}

/**
 * 从Actor获取PawnCombatComponent组件
 * 
 * @param InActor - 要获取组件的目标Actor
 * @return 返回找到的PawnCombatComponent指针，如果未找到则返回nullptr
 * 
 * 实现细节:
 * 1. 首先检查传入的Actor是否有效
 * 2. 尝试将Actor转换为IPawnCombatInterface接口
 * 3. 如果转换成功，通过接口获取PawnCombatComponent
 * 4. 如果转换失败或Actor未实现接口，返回nullptr
 */
UPawnCombatComponent* UWarriorBlueprintFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	// 检查传入的Actor是否有效
	check(InActor);

	// 尝试将Actor转换为IPawnCombatInterface接口
	if (const IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		// 如果转换成功，通过接口获取PawnCombatComponent
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	// 如果转换失败或Actor未实现接口，返回nullptr
	return nullptr;
}

/**
 * 蓝图版本的从Actor获取PawnCombatComponent组件函数
 * 
 * @param InActor - 要获取组件的目标Actor
 * @param OutValidType - 输出参数，表示获取结果是否有效(Valid/Invalid)
 * @return 返回找到的PawnCombatComponent指针，如果未找到则返回nullptr
 * 
 * 该函数是NativeGetPawnCombatComponentFromActor的蓝图版本:
 * 1. 调用原生获取函数获取组件
 * 2. 根据获取结果设置有效性类型
 * 3. 返回获取到的组件
 */
UPawnCombatComponent* UWarriorBlueprintFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EWarriorValidType& OutValidType)
{
	//NativeGetPawnCombatComponentFromActor 我们自己写的 就在这个类里面
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	// 根据组件获取结果设置有效性类型
	OutValidType = CombatComponent ? EWarriorValidType::Valid : EWarriorValidType::Invalid;

	return CombatComponent;
}

/**
 * 检查目标Pawn是否敌对
 * 
 * @param QueryPawn - 查询发起者的Pawn
 * @param TargetPawn - 要检查的目标Pawn
 * @return 如果两个Pawn属于不同队伍返回true，否则返回false
 * 
 * 实现细节:
 * 1. 检查两个Pawn是否有效
 * 2. 获取两个Pawn的Controller并转换为IGenericTeamAgentInterface接口
 * 3. 如果两个Controller都实现了接口，比较它们的队伍ID
 * 4. 如果队伍ID不同，说明是敌对关系
 * 5. 如果任一Controller未实现接口，默认返回false
 */
bool UWarriorBlueprintFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	// 检查两个Pawn是否有效
	check(QueryPawn && TargetPawn);

	// 获取两个Pawn的Controller并转换为IGenericTeamAgentInterface接口
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	// 如果两个Controller都实现了接口，比较它们的队伍ID
	if (QueryTeamAgent && TargetTeamAgent)
	{
		// 队伍ID不同说明是敌对关系
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	// 如果任一Controller未实现接口，默认返回false
	return false;
}

/**
 * 获取可缩放浮点值在指定等级的值
 * 
 * @param InScalableFloat - 要获取值的可缩放浮点对象
 * @param InLevel - 要获取值的等级
 * @return 返回指定等级下的浮点值
 */
float UWarriorBlueprintFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat,
                                                                     float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

/**
 * 计算受击反应方向标签
 * 
 * @param InAttacker - 攻击者Actor
 * @param InVictim - 受击者Actor
 * @param OutAngleDifference - 输出参数，表示攻击方向与受击者前向的夹角
 * @return 返回受击反应方向的GameplayTag
 * 
 * 实现细节:
 * 1. 检查输入参数有效性
 * 2. 获取受击者的前向向量
 * 3. 计算攻击者到受击者的归一化方向向量
 * 4. 计算两个向量的点积，用于确定夹角
 * 5. 使用反余弦计算实际角度值
 * 6. 通过叉积判断攻击方向在受击者的左侧还是右侧
 * 7. 根据叉积结果调整角度值的正负号
 */
FGameplayTag UWarriorBlueprintFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim,
                                                                           float& OutAngleDifference)
{
	// 检查输入参数有效性
	check(InAttacker && InVictim);

	// 获取受击者的前向向量
	const FVector VictimForward = InVictim->GetActorForwardVector();

	// 计算攻击者到受击者的归一化方向向量
	const FVector VictimAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).
		GetSafeNormal();

	// 计算两个向量的点积，用于确定夹角
	const float DotResult = FVector::DotProduct(VictimForward, VictimAttackerNormalized);

	// 使用反余弦计算实际角度值
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	// 通过叉积判断攻击方向在受击者的左侧还是右侧
	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimAttackerNormalized);

	// 如果叉积的Z分量小于0，说明攻击方向在受击者的左侧，将角度设为负值
	if (CrossResult.Z < 0.0f)
	{
		OutAngleDifference *= -1.0f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Right;
	}

	return WarriorGameplayTags::Shared_Status_HitReact_Front;
}

bool UWarriorBlueprintFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);
	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(),
	                                            InDefender->GetActorForwardVector());

	return DotResult < -0.1f;
}

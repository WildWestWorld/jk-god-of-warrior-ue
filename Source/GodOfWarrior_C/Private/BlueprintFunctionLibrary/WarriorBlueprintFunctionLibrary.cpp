// Jackie Lee .All Rights Reserved


#include "BlueprintFunctionLibrary/WarriorBlueprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

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

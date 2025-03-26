// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarriorBlueprintFunctionLibrary.generated.h"

// 前向声明UWarriorAbilitySystemComponent类
class UWarriorAbilitySystemComponent;

/**
 * 确认类型枚举
 * 用于表示确认结果的两种状态
 */
UENUM()
enum class EWarriorConfirmType : uint8
{
	Yes, // 确认/是
	No // 否定/否
};

/**
 * 战士蓝图函数库
 * 包含一些通用的静态辅助函数，可以在蓝图中调用
 * 这个类继承自UBlueprintFunctionLibrary，用于提供蓝图可调用的工具函数
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * 从Actor获取WarriorAbilitySystemComponent组件
	 * 
	 * @param InActor - 要获取组件的Actor对象
	 * @return 返回Actor上的WarriorAbilitySystemComponent组件，如果没有则返回nullptr
	 * 
	 * 这是一个原生C++实现的静态函数，用于在C++和蓝图中获取Actor的能力系统组件
	 * 主要用于:
	 * 1. 检查Actor是否具有能力系统组件
	 * 2. 获取Actor的能力系统组件以进行后续操作
	 */
	static UWarriorAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);

	/**
	 * 如果Actor没有指定的GameplayTag，则添加它
	 * 
	 * @param InActor - 要添加标签的目标Actor
	 * @param TagToAdd - 要添加的GameplayTag
	 * 
	 * 该函数会检查Actor是否已有指定标签，如果没有则添加
	 * 可在蓝图中调用，用于动态管理Actor的GameplayTag
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|BlueprintFunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	/**
	 * 如果Actor有指定的GameplayTag，则移除它
	 * 
	 * @param InActor - 要移除标签的目标Actor
	 * @param TagToRemove - 要移除的GameplayTag
	 * 
	 * 该函数会检查Actor是否有指定标签，如果有则移除
	 * 可在蓝图中调用，用于动态管理Actor的GameplayTag
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|BlueprintFunctionLibrary")
	static void RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	/**
	 * 检查Actor是否拥有指定的GameplayTag
	 * 
	 * @param InActor - 要检查的目标Actor
	 * @param TagToCheck - 要检查的GameplayTag
	 * @return 如果Actor拥有指定标签返回true，否则返回false
	 * 
	 * 这是一个原生C++实现的函数，用于检查Actor是否具有特定的GameplayTag
	 */
	static bool NativeIsActorHasTag(AActor* InActor, FGameplayTag TagToCheck);

	/**
	 * 蓝图版本的Actor标签检查函数
	 * 
	 * @param InActor - 要检查的目标Actor
	 * @param TagToCheck - 要检查的GameplayTag
	 * @param OutConfirmType - 输出参数，表示检查结果(Yes/No)
	 * 
	 * 该函数是NativeDoseActorHasTag的蓝图版本
	 * 通过OutConfirmType参数返回检查结果
	 * meta标签中的ExpandEnumAsExecs表示在蓝图中将枚举展开为执行引脚
	 */
	UFUNCTION(BlueprintCallable, Category = "Warrior|BlueprintFunctionLibrary",
		meta=(DisplayName="Is Actor Has Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void BP_IsActorHasTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType);
};

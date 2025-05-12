// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarriorTypes/WarriorEnumTypes.h"
#include "WarriorBlueprintFunctionLibrary.generated.h"

struct FScalableFloat;
class UPawnCombatComponent;
// 前向声明UWarriorAbilitySystemComponent类
class UWarriorAbilitySystemComponent;


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
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

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


	/**
	 * 从Actor获取PawnCombatComponent组件
	 * 
	 * @param InActor - 要获取组件的目标Actor
	 * @return 返回找到的PawnCombatComponent指针，如果未找到则返回nullptr
	 * 
	 * 该函数会检查Actor是否实现了IPawnCombatInterface接口
	 * 如果实现了接口，则通过接口获取PawnCombatComponent
	 * 这是一个原生C++实现的辅助函数
	 */
	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);


	UFUNCTION(BlueprintCallable, Category = "Warrior|BlueprintFunctionLibrary",
		meta=(DisplayName="Get Pawn Combat Component From Actor", ExpandEnumAsExecs="OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EWarriorValidType& OutValidType);


	UFUNCTION(BlueprintCallable, Category = "Warrior|BlueprintFunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Warrior|BlueprintFunctionLibrary",
		meta=(CompactNodeTitle="Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel);

	UFUNCTION(BlueprintPure, Category = "Warrior|BlueprintFunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "Warrior|BlueprintFunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);
};

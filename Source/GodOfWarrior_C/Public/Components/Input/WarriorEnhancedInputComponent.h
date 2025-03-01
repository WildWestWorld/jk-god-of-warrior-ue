// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorEnhancedInputComponent.generated.h"

/**
 * 自定义的增强输入组件类
 * 继承自UEnhancedInputComponent,用于处理游戏中的输入绑定
 * 提供了绑定原生输入动作和技能输入动作的功能
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	/**
	 * 绑定原生输入动作的模板函数
	 * @tparam UserObject - 持有回调的对象类型(通常是UObject的派生类)
	 * @tparam CallbackFunc - 回调函数的类型(通常是成员函数指针)
	 * @param InputConfig - 指向输入配置数据资产
	 * @param InputTag - 用于标识特定输入动作的GameplayTag
	 * @param TriggerEvent - 定义触发事件的类型(如按下、释放等)
	 * @param ContextObject - 指向将接收回调的对象实例
	 * @param Func - 实际的回调函数
	 */
	template <class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig *InputConfig, const FGameplayTag &InputTag,
							   ETriggerEvent TriggerEvent, UserObject *ContextObject, CallbackFunc Func);

	/**
	 * 绑定技能输入动作的模板函数
	 * @tparam UserObject - 持有回调的对象类型
	 * @tparam CallbackFunc - 回调函数的类型
	 * @param InputConfig - 输入配置数据资产
	 * @param ContextObject - 接收回调的对象实例
	 * @param InputPressedFunc - 按下输入时的回调函数
	 * @param InputReleasedFunc - 释放输入时的回调函数
	 */
	template <class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig *InputConfig, UserObject *ContextObject,
								CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

/**
 * BindNativeInputAction函数的具体实现
 * 用于将原生输入动作绑定到指定的回调函数
 *
 * 实现步骤:
 * 1. 检查输入配置是否有效
 * 2. 通过GameplayTag查找对应的输入动作
 * 3. 如果找到对应动作,则进行绑定
 */
template <class UserObject, typename CallbackFunc>
void UWarriorEnhancedInputComponent::BindNativeInputAction(
	const UDataAsset_InputConfig *InputConfig, // 输入配置数据资产
	const FGameplayTag &InputTag,			   // 用于标识输入动作的GameplayTag
	ETriggerEvent TriggerEvent,				   // 输入触发的时机（如：按下、释放）
	UserObject *ContextObject,				   // 接收输入事件的对象
	CallbackFunc Func)						   // 输入触发时要调用的函数
{
	// 检查输入配置是否有效，如果无效则输出错误信息
	checkf(InputConfig, TEXT("Input config data is null,can not proceed with binding"))

		// 通过GameplayTag查找对应的输入动作
		if (const UInputAction *FoundAction = InputConfig->FindNativeInputActionByTag(InputTag))
	{
		// 如果找到对应的输入动作，则进行绑定
		// 将输入动作、触发条件、上下文对象和回调函数关联起来
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

/**
 * BindAbilityInputAction函数的具体实现
 * 用于将技能输入动作绑定到指定的回调函数
 *
 * 实现步骤:
 * 1. 检查输入配置的有效性
 * 2. 遍历所有技能输入动作配置
 * 3. 对每个有效的配置:
 *    - 绑定按下事件到InputPressedFunc
 *    - 绑定释放事件到InputReleasedFunc
 */
template <class UserObject, typename CallbackFunc>
void UWarriorEnhancedInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig *InputConfig,
															UserObject *ContextObject, CallbackFunc InputPressedFunc,
															CallbackFunc InputReleasedFunc)
{
	// 检查输入配置是否有效，如果无效则输出错误信息
	checkf(InputConfig, TEXT("Input config data is null,can not proceed with binding"));

	// 遍历所有技能输入动作配置
	for (const FWarriorInputActionConfig &AbilityInputActionConfig : InputConfig->AbilityInputActions)
	{
		// 跳过无效的输入动作配置
		if (!AbilityInputActionConfig.IsValid())
		{
			continue;
		}

		// 绑定按下输入事件到对应的回调函数
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc,
				   AbilityInputActionConfig.InputTag);

		// 绑定释放输入事件到对应的回调函数
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc,
				   AbilityInputActionConfig.InputTag);
	}
}

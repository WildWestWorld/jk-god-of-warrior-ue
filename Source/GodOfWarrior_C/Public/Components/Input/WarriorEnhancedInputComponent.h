// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// 模板参数:
	// UserObject: 类模板参数，表示持有回调的对象类型（通常是 UObject 的派生类）
	// CallbackFunc: 类型模板参数，表示回调函数的类型（通常是成员函数指针）
	// 函数参数:
	// InputConfig: const UDataAsset_InputConfig* 类型，指向输入配置数据资产   UDataAsset_InputConfig是我们自己写的
	// InputTag: const FGameplayTag& 类型，用于标识特定的输入动作
	// TriggerEvent: ETriggerEvent 枚举类型，定义触发事件的类型（如按下、释放等）
	// ContextObject: UserObject* 类型，指向将接收回调的对象实例
	// Func: CallbackFunc 类型，实际的回调函数
	template <class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InputConfig, const FGameplayTag& InputTag,
	                           ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
};

/**
 * 绑定原生输入动作到指定的回调函数
 * @tparam UserObject - 上下文对象的类型（通常是玩家控制器或角色类）
 * @tparam CallbackFunc - 回调函数的类型
 * @param InputConfig - 包含输入动作映射的数据资产
 * @param InputTag - 用于识别特定输入动作的GameplayTag
 * @param TriggerEvent - 定义何时触发此输入动作（如按下、释放等）
 * @param ContextObject - 将接收输入事件的对象实例
 * @param Func - 输入触发时要执行的回调函数
 */
template <class UserObject, typename CallbackFunc>
void UWarriorEnhancedInputComponent::BindNativeInputAction(
	const UDataAsset_InputConfig* InputConfig, // 输入配置数据资产
	const FGameplayTag& InputTag, // 用于标识输入动作的GameplayTag
	ETriggerEvent TriggerEvent, // 输入触发的时机（如：按下、释放）
	UserObject* ContextObject, // 接收输入事件的对象
	CallbackFunc Func) // 输入触发时要调用的函数
{
	// 检查输入配置是否有效，如果无效则输出错误信息
	checkf(InputConfig, TEXT("Input config data is null,can not proceed with binding"))

	// 通过GameplayTag查找对应的输入动作
	if (const UInputAction* FoundAction = InputConfig->FindNativeInputActionByTag(InputTag))
	{
		// 如果找到对应的输入动作，则进行绑定
		// 将输入动作、触发条件、上下文对象和回调函数关联起来
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

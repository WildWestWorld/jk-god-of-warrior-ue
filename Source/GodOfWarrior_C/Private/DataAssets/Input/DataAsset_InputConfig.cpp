// Jackie Lee .All Rights Reserved


#include "DataAssets/Input/DataAsset_InputConfig.h"

// 在这个函数声明中,末尾的 const 表示这是一个常成员函数(const member function)。它有以下含义:
//
// 这个成员函数不会修改类的任何成员变量的值(除非成员变量被声明为 mutable)
// 在这个函数内部,不能调用该类的非 const 成员函数
// 这个函数可以被 const 对象调用
UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InputTag) const
{
	// 遍历 NativeInputActions 数组中的每个元素
	// NativeInputActions 定义在.h文件里面7
	// TArray<FWarriorInputActionConfig> NativeInputActions; // 存储多个 FWarriorInputActionConfig 对象的数组，用于存储具体的输入动作配置。
	for (const FWarriorInputActionConfig& InputActionConfig : NativeInputActions)
	{
		// 判断当前元素的 InputTag 是否匹配，并且该 InputAction 是否有效
		if (InputActionConfig.InputTag == InputTag && InputActionConfig.InputAction)
		{
			// 如果匹配成功，返回对应的 UInputAction 对象
			return InputActionConfig.InputAction;
		}
	}
	// 如果没有找到匹配的标签，返回 nullptr
	return nullptr;
}

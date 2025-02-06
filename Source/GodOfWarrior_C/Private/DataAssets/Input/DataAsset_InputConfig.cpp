// Jackie Lee .All Rights Reserved


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InputTag)
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

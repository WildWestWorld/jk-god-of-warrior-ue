// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_InputConfig.generated.h"

// 这个类来自于EnhancedInput
class UInputAction; // UInputAction 用于表示输入的动作，例如按键、鼠标点击等。
class UInputMappingContext; // UInputMappingContext 用于定义输入上下文，管理与不同输入设备和输入配置的映射关系。

// USTRUCT(BlueprintType) 的意思是声明这个结构体 FWarriorInputActionConfig 能够在蓝图中使用。
USTRUCT(BlueprintType)
// 结构体适用于简单的数据存储，默认访问权限是 public，通常没有复杂的功能，更多用于存储数据。
struct FWarriorInputActionConfig
{
	// GENERATED_BODY() 是 Unreal Engine 中的一种宏，它用于自动生成与类或结构体相关的代码。
	GENERATED_BODY()

	// 属性 InputTag: 只能在编辑器中设置，且在蓝图中只读，表示与输入相关的标签
	// meta=(Categories="InputTag") 指定了标签的分类，用于编辑器中的组织
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="InputTag"))
	// 标签的分类：FGameplayTag 可以分配到不同的类别（通过 meta=(Categories="...")），使得它能够在编辑器中更清晰地进行组织和分类。
	// 比如，“攻击”操作可以归类到“动作类”标签下，而“跳跃”操作可以归类到“移动类”标签下。
	FGameplayTag InputTag; // 用于标识输入的标签，例如用于区分不同的输入类型或输入配置。
	// UInputAction 是用于表示输入动作的对象，可以包含按键、手势等输入动作。
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction; // 这是一个指向 UInputAction 类型的指针，用于指定输入操作的实际逻辑。
};

/**
 * 这个类是用于配置输入操作的DataAsset类，可以在编辑器中创建配置文件，用于保存输入配置数据。 这样我们就能在 编辑器Data_Asset 中拿到这个我们自定义的类了
 */
UCLASS()
// GODOFWARRIOR_C_API 是一个宏，用于标记类或函数在模块间的访问权限，通常用于跨模块的访问。
class GODOFWARRIOR_C_API UDataAsset_InputConfig : public UDataAsset
{
	// GENERATED_BODY() 是 Unreal Engine 中的一种宏，它用于自动生成与类或结构体相关的代码。
	GENERATED_BODY()

public:
	// DefaultMappingContext：默认的输入映射上下文。可以通过这个属性配置默认的输入映射规则。
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext; // UInputMappingContext 用于定义输入映射上下文，关联输入设备与动作的映射关系。

	// NativeInputActions：包含多个输入动作配置。这个数组包含了所有与输入动作相关的配置，可以在编辑器中进行编辑。
	// meta=(TitleProperty="InputAction") 指定了该属性在编辑器或UI中作为标题的显示方式，可能与输入动作（例如，按键映射）相关。
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	// FWarriorInputActionConfig 是我们自定义的结构体类型，用于存储单个输入动作的配置。
	TArray<FWarriorInputActionConfig> NativeInputActions; // 存储多个 FWarriorInputActionConfig 对象的数组，用于存储具体的输入动作配置。

	//根据Tag查找对应的InputAction
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InputTag);
};

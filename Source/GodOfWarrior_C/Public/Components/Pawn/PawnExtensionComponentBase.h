// Jackie Lee .All Rights Reserved

#pragma once  // 确保头文件只被包含一次

#include "CoreMinimal.h"  // 包含Unreal Engine核心最小化头文件
#include "Components/ActorComponent.h"  // 包含ActorComponent基类
#include "PawnExtensionComponentBase.generated.h"  // 包含由Unreal自动生成的头文件


// 定义一个可在蓝图中生成的组件类，归类为"Custom"组
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODOFWARRIOR_C_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY() // Unreal的宏，为类生成必要的反射代码
public:
	// 添加构造函数声明
	UPawnExtensionComponentBase();

protected:
	/**
	 * 获取拥有此组件的Pawn对象并转换为指定类型
	 * 
	 * @tparam T 目标Pawn类型，必须是APawn的子类
	 * @return 返回转换后的Pawn指针，类型为T
	 */
	template <class T>
	T* GetOwningPawn() const
	{
		// 静态断言确保T类型可以从APawn转换而来
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value,
		              "T Template Parameter to GetPawn must be derived from APawn");

		// 将当前组件的拥有者转换为T类型并返回
		// CastChecked会在转换失败时触发断言错误
		return CastChecked<T>(GetOwner());
	}

	/**
	 * 获取拥有此组件的Pawn对象的非模板版本
	 * 
	 * @return 返回基础APawn类型的指针
	 */
	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	/**
	 * 获取控制拥有此组件的Pawn的Controller并转换为指定类型
	 * 
	 * @tparam T 目标Controller类型，必须是AController的子类
	 * @return 返回转换后的Controller指针，类型为T
	 */
	template <class T>
	T* GetOwningController() const
	{
		// 静态断言确保T类型可以从AController转换而来
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value,
		              "T Template Parameter to GetController must be derived from AController");

		// 获取拥有此组件的Pawn，然后获取其Controller并转换为T类型
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};

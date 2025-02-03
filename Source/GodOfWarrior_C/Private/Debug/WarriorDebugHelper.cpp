#include "Debug/WarriorDebugHelper.h"

namespace Debug
{
	void Print(const FString& Msg, const FColor& Color, int32 InKey)
	{
		// 		GEngine 是 Unreal Engine 中的全局引擎指针，指向当前的引擎实例。这个检查确保只有在 GEngine 有效时才执行后续代码。
		// 如果引擎（GEngine）没有初始化或无效，则不会执行消息打印逻辑。
		if (GEngine)
		{
			// 这行代码会将 Msg 打印到屏幕上，显示在游戏窗口的顶部。GEngine->AddOnScreenDebugMessage 是 Unreal Engine 提供的一个函数，用于将调试消息显示在屏幕上。
			// InKey 是用于标识消息的唯一键。可以用不同的键值来区分多个消息。
			// 7.f 是消息显示的持续时间（单位：秒）。在这里，消息将显示 7 秒。
			// Color 是显示消息时使用的颜色。
			// Msg 是要显示的消息内容。
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, Msg);
			// 这行代码将消息打印到 Unreal Engine 的日志中。
			// LogTemp 是一个默认的日志类别，通常用于临时的调试日志。
			// Warning 是日志的严重级别，表示警告信息（其他可能的级别有 Error, Log, 等）。
			// TEXT("%s") 是格式化字符串，它将 Msg 打印成一个字符串格式。TEXT 宏用于确保字符串在 Unreal Engine 中的 Unicode 字符编码。
			// *Msg 是 FString 类型转为 const TCHAR* 类型。FString 是 Unreal Engine 的字符串类，* 操作符用于获取它的内部数据指针（字符数组）

			// 			为什么需要 *？
			// 在 UE_LOG 中，你传递的消息应该是 const TCHAR* 类型，因为 UE_LOG 使用 C 风格的字符串格式（%s 需要 const TCHAR* 类型）。
			// FString 不是一个 const TCHAR*，它是一个封装了字符数组的对象，所以你需要解引用（通过 *）来获得指向字符数组的指针。
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}
}

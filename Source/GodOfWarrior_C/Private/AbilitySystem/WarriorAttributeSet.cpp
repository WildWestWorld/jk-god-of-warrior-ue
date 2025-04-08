// Jackie Lee .All Rights Reserved


#include "AbilitySystem/WarriorAttributeSet.h"
// 引入FGameplayEffectModCallbackData类型的头文件
#include  "GameplayEffectExtension.h"
// 引入调试辅助工具头文件
#include "BlueprintFunctionLibrary/WarriorBlueprintFunctionLibrary.h"
#include "Debug/WarriorDebugHelper.h"
#include "GameplayTags/WarriorGameplayTags.h"

/**
 * 构造函数,初始化角色的基础属性值
 * 所有属性初始值设为1.0
 * 包括:
 * - 当前生命值
 * - 最大生命值  
 * - 当前怒气值
 * - 最大怒气值
 * - 攻击力
 * - 防御力
 */
UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f); // 初始化当前生命值
	InitMaxHealth(1.f); // 初始化最大生命值
	InitCurrentRage(1.f); // 初始化当前怒气值
	InitMaxRage(1.f); // 初始化最大怒气值
	InitAttackPower(1.f); // 初始化攻击力
	InitDefencePower(1.f); // 初始化防御力
}

/**
 * 游戏效果执行后的处理函数
 * 主要处理生命值、怒气值和伤害的变化
 */
void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// 调用父类实现
	Super::PostGameplayEffectExecute(Data);

	// 如果修改的是生命值属性
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		// 限制生命值在0到最大生命值之间
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
	}

	// 如果修改的是怒气值属性 
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		// 限制怒气值在0到最大怒气值之间
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
	}

	// 如果是受到伤害
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		// 获取当前生命值
		const float OldHealth = GetCurrentHealth();
		// 获取受到的伤害值
		const float DamageDone = GetDamageTaken();
		// 计算并限制新的生命值
		// Clamp函数用于限制一个值在指定范围内
		// 参数1: 要限制的值 (这里是 OldHealth - DamageDone)
		// 参数2: 最小值 (这里是 0.f)
		// 参数3: 最大值 (这里是 GetMaxHealth())
		// 如果值小于最小值,返回最小值
		// 如果值大于最大值,返回最大值
		// 否则返回原值
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		// 创建调试信息
		const FString DebugString = FString::Printf(
			TEXT("Old Health:%f,Damage Done:%f,NewCurrentHealth: %f"), OldHealth, DamageDone, NewCurrentHealth);
		// 打印调试信息
		Debug::Print(DebugString, FColor::Green);

		// 如果生命值为0,预留死亡处理位置
		if (NewCurrentHealth == 0.f)
		{
			UWarriorBlueprintFunctionLibrary::AddGameplayTagToActorIfNone(
				Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Dead);
		}
	}
}

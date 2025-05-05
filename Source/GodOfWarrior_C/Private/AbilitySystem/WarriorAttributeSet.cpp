// Jackie Lee .All Rights Reserved


#include "AbilitySystem/WarriorAttributeSet.h"
// 引入FGameplayEffectModCallbackData类型的头文件
#include  "GameplayEffectExtension.h"
// 引入调试辅助工具头文件
#include "BlueprintFunctionLibrary/WarriorBlueprintFunctionLibrary.h"
#include "Components/Pawn/UI/PawnUIComponent.h"
#include "Components/Pawn/UI/Player/HeroUIComponent.h"
#include "Debug/WarriorDebugHelper.h"
#include "GameplayTags/WarriorGameplayTags.h"
#include "Interfaces/PawnUIInterface.h"

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
 * @param Data - 游戏效果修改回调数据,包含目标Actor和修改的属性信息
 */
void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// 调用父类实现
	Super::PostGameplayEffectExecute(Data);

	// 如果UI接口指针无效,则从目标Actor获取并缓存
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	// 确保目标Actor实现了UI接口
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"),
	       *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	// 获取UI组件
	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	// 确保成功获取到UI组件
	checkf(PawnUIComponent, TEXT("Couldn't extract a PawnUIComponent from &s"),
	       *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	// 处理生命值变化
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		// 限制生命值在0到最大生命值之间
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		// 广播生命值百分比变化事件
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	// 处理怒气值变化
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		// 限制怒气值在0到最大怒气值之间
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);

		// 如果是英雄角色,广播怒气值百分比变化事件
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	// 处理受到伤害
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		// 获取当前生命值和受到的伤害值
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		// 计算并限制新的生命值
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		// 创建并打印调试信息
		// const FString DebugString = FString::Printf(
		// 	TEXT("Old Health:%f,Damage Done:%f,NewCurrentHealth: %f"), OldHealth, DamageDone, NewCurrentHealth);
		// Debug::Print(DebugString, FColor::Green);

		// 广播生命值百分比变化事件
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		// 如果生命值降为0,添加死亡状态标签
		if (GetCurrentHealth() == 0.f)
		{
			UWarriorBlueprintFunctionLibrary::AddGameplayTagToActorIfNone(
				Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Dead);
		}
	}
}

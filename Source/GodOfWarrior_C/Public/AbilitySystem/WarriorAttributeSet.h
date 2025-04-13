// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"

#include "WarriorAttributeSet.generated.h"

//使用这个得加上头文件 #include "AbilitySystem/WarriorAbilitySystemComponent.h"
/**
 * 定义属性访问器宏,用于生成属性的getter/setter方法
 * @param ClassName - 类名
 * @param PropertyName - 属性名
 * 生成以下访问器:
 * - 属性getter
 * - 值getter 
 * - 值setter	
 * - 值初始化器
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class IPawnUIInterface;
/**
 * 角色属性集类,用于管理角色的各种属性数值
 * 包含生命值、怒气值、攻击力和防御力等基础属性
 */
UCLASS()
class GODOFWARRIOR_C_API UWarriorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	/** 构造函数,初始化属性默认值 */
	UWarriorAttributeSet();

	//来自于父级 AttributeSet
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/** 当前生命值 */
	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentHealth)

	/** 最大生命值 */
	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxHealth)

	/** 当前怒气值 */
	UPROPERTY(BlueprintReadOnly, Category="Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentRage)

	/** 最大怒气值 */
	UPROPERTY(BlueprintReadOnly, Category="Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxRage)

	/** 攻击力 */
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, AttackPower)

	/** 防御力 */
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DefencePower;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DefencePower)


	/** 伤害 */
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DamageTaken)

private:
	/** 缓存的PawnUI接口指针 
	 * 用于存储对实现了IPawnUIInterface的对象的弱引用
	 * 主要用于更新UI显示,如生命值、怒气值等属性变化
	 */
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
};

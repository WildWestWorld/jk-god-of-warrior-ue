// Jackie Lee .All Rights Reserved


#include "AbilitySystem/EffectExecutionCalculation/DamageTakenEffectCalculation.h"

#include "AbilitySystem/WarriorAttributeSet.h"
#include "Debug/WarriorDebugHelper.h"
#include "GameplayTags/WarriorGameplayTags.h"
/**
 * 伤害承受效果计算类的构造函数
 * 用于初始化伤害计算所需的属性捕获定义
 * 
 * 这个类主要用于:
 * 1. 捕获攻击者的攻击力属性和防御者的防御力属性
 * 2. 设置如何获取和使用这些属性值
 * 
 * 工作流程:
 * 1. 声明需要捕获的属性(攻击力和防御力)
 * 2. 在构造函数中定义属性捕获规则
 * 3. 提供静态访问方法以复用捕获定义
 */
struct FWarriorDamageCapture
{
	// 声明需要捕获的攻击力属性
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	// 声明需要捕获的防御力属性
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefencePower)

	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	/**
	 * 构造函数 - 定义属性捕获规则
	 * UWarriorAttributeSet: 属性所在的类
	 * AttackPower: 要捕获的攻击力属性
	 * Source: 从效果发起者(攻击者)处获取
	 * false: 不创建属性值快照,使用实时值
	 * 
	 * DefencePower: 要捕获的防御力属性
	 * Target: 从效果接收者(防御者)处获取
	 */
	FWarriorDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DefencePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DamageTaken, Target, false)
	}
};

/**
 * 获取伤害捕获定义的静态方法
 * 使用静态局部变量确保只创建一个实例
 * @return 返回伤害捕获定义的常量引用
 */
static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
	static FWarriorDamageCapture WarriorDamageCapture;
	return WarriorDamageCapture;
}

UDamageTakenEffectCalculation::UDamageTakenEffectCalculation()
{
	//这个方法是慢捕获
	// // 第一步:获取攻击力属性的指针
	// // FindFieldChecked: 在指定类中查找属性,如果找不到会报错
	// // UWarriorAttributeSet::StaticClass(): 获取属性集类的类型信息
	// // GET_MEMBER_NAME_CHECKED: 安全地获取类成员变量名,编译时会检查该成员是否存在
	// FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	// 	UWarriorAttributeSet::StaticClass(),
	// 	GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet, AttackPower) // AttackPower是属性集中定义的攻击力属性
	// );
	//
	// // 第二步:创建属性捕获定义
	// // 参数1 AttackPowerProperty: 指定要捕获哪个属性(这里是攻击力)
	// // 参数2 Source: 指定从哪里获取属性值
	// //   - Source表示从效果的发起者(比如攻击者)那里获取
	// //   - Target则表示从效果的接收者(比如被攻击者)那里获取
	// // 参数3 false: 是否创建属性值的快照
	// //   - true表示创建快照,即固定在效果开始时的值
	// //   - false表示不创建快照,使用实时值
	// FGameplayEffectAttributeCaptureDefinition AttributeCaptureDefinition(
	// 	AttackPowerProperty,
	// 	EGameplayEffectAttributeCaptureSource::Source,
	// 	false
	// );
	//
	// // 第三步:将这个属性捕获定义添加到要使用的属性列表中
	// // RelevantAttributesToCapture是父类定义的数组,存储所有需要捕获的属性
	// // 在后续的伤害计算中,会使用这个列表中的所有属性进行计算
	// RelevantAttributesToCapture.Add(AttributeCaptureDefinition);


	//快速 获取方法
	// 添加攻击力属性捕获定义到捕获列表中
	// 通过GetWarriorDamageCapture()获取预定义的捕获配置
	// AttackPowerDef包含了从Source(攻击者)获取攻击力属性的设置
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef);

	// 添加防御力属性捕获定义到捕获列表中
	// DefencePowerDef包含了从Target(防御者)获取防御力属性的设置
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefencePowerDef);


	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageTakenDef);
}

void UDamageTakenEffectCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().AttackPowerDef, EvaluateParams,
	                                                           SourceAttackPower);

	Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}
		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}


	float TargetDefencePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefencePowerDef,
	                                                           EvaluateParams, TargetDefencePower);
	Debug::Print(TEXT("TargetDefencePower"), TargetDefencePower);
	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
		Debug::Print(TEXT("ScaleBaseDamageLight"), BaseDamage);
	}
	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
		Debug::Print(TEXT("ScaleBaseDamageHeavy"), BaseDamage);
	}
	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefencePower;

	Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);
	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			GetWarriorDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamageDone));
	}
}

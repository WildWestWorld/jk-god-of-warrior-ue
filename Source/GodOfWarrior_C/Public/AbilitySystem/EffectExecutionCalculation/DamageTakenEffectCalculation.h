// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageTakenEffectCalculation.generated.h"

/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API UDamageTakenEffectCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UDamageTakenEffectCalculation();

	//来自 父级 UGameplayEffectExecutionCalculation 的方法
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

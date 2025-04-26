// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Pawn/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	/**
 * 当武器击中目标角色时调用
 * @param HitActor - 被击中的目标角色
 */
	virtual void OnHitTargetActor(AActor* HitActor) override;
};

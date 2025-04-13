// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Pawn/UI/PawnUIComponent.h"
#include "HeroUIComponent.generated.h"

/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API UHeroUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	//FOnPercentChangedDelegate 可用是因为 UPawnUIComponent
	//因为Rage是人物特殊 所以我们就自己写
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;
};

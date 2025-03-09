// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API AWarriorHeroWeapon : public AWarriorWeaponBase
{
	GENERATED_BODY()

public:
	//装备上Data
	//在FWarriorHeroWeaponData 在 WarriorStructTypes定义
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWarriorHeroWeaponData HeroWeaponData;
};

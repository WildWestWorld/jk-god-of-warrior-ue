// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorHeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API AWarriorHeroCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()

protected:
	// protected：这个访问修饰符表示 BeginPlay 函数只能在类内部以及派生类中访问，外部不能访问。
	// virtual：这个关键字表示该函数是虚函数，派生类可以覆盖（重写）它。
	// void：表示该函数没有返回值。
	// BeginPlay()：这是函数名，表示在 Actor 创建时或游戏开始时调用的函数。
	// override：表示你正在重写基类中的 BeginPlay 函数。如果基类中没有这个函数或签名不匹配，编译器会给出错误提示。
	virtual void BeginPlay() override;
};

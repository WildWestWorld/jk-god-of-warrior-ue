// Jackie Lee .All Rights Reserved


#include "Characters/WarriorHeroCharacter.h"

// 添加调试器
#include "Debug/WarriorDebugHelper.h"

void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Debug 命名空间
	//Print调用 命名空间的打印函数
	Debug::Print(TEXT("Working"));
}

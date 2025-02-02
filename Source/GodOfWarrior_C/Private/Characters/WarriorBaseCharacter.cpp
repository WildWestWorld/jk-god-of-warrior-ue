// Jackie Lee .All Rgihts Reserved


#include "Characters/WarriorBaseCharacter.h"

// Sets default values
AWarriorBaseCharacter::AWarriorBaseCharacter()
{
 		// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// “将该角色的 Tick() 函数在游戏开始时禁用。”
	PrimaryActorTick.bStartWithTickEnabled = false;
	// 该角色的网格（GetMesh()）不接收贴花效果（如血迹、污渍、投射阴影等）。
	GetMesh()->bReceivesDecals = false;
}




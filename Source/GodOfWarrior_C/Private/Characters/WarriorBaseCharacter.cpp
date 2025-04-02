// Jackie Lee .All Rgihts Reserved


#include "Characters/WarriorBaseCharacter.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/WarriorAttributeSet.h"

// Sets default values
AWarriorBaseCharacter::AWarriorBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// “将该角色的 Tick() 函数在游戏开始时禁用。”
	PrimaryActorTick.bStartWithTickEnabled = false;
	// 该角色的网格（GetMesh()）不接收贴花效果（如血迹、污渍、投射阴影等）。
	GetMesh()->bReceivesDecals = false;


	// CreateDefaultSubobject 只能在构造函数中调用
	// 通过这种方式创建的组件会自动被虚幻引擎的垃圾回收系统管理
	// TEXT宏的使用是虚幻引擎的编码规范，用于支持跨平台的字符串处理


	// 创建并初始化战士的能力系统组件(Ability System Component)
	// CreateDefaultSubobject: UE中用于在构造函数中创建组件的函数
	// TEXT(): UE中用于处理字符串的宏，将字符串转换为TCHAR类型
	// "WarriorAbilitySystemComponent": 组件的唯一标识名称
	WarriorAbilitySystemComponent = CreateDefaultSubobject<UWarriorAbilitySystemComponent>(
		TEXT("WarriorAbilitySystemComponent"));

	// 创建并初始化战士的属性集合(Attribute Set)
	// 属性集合用于存储和管理角色的各种属性数值(比如生命值、魔法值、攻击力等)
	// CreateDefaultSubobject: 在构造阶段创建子对象/子组件
	// UWarriorAttributeSet: 自定义的属性集合类
	// "WarriorAttributeSet": 属性集合的唯一标识名称
	WarriorAttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>(TEXT("WarriorAttributeSet"));
}

//方法 来自 IAbilitySystemInterface 继承IAbilitySystemInterface 必须实现,需要返回UWarriorAbilitySystemComponent 类型  不然报错
UAbilitySystemComponent* AWarriorBaseCharacter::GetAbilitySystemComponent() const
{
	//是我们自己的方法 返回UWarriorAbilitySystemComponent 在WarriorBaseCharacter.h 定义的
	//返回UWarriorAbilitySystemComponent 在AWarriorBaseCharacter 初始化的时候 就设置了，所以能拿到
	return GetWarriorAbilitySystemComponent();
}

UPawnCombatComponent* AWarriorBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

//生命周期
/**
* 当角色被控制器接管时调用的函数
* 用于初始化角色的能力系统和其他必要设置
* 
* @param NewController 接管该角色的控制器(可能是玩家控制器或AI控制器)
*/
void AWarriorBaseCharacter::PossessedBy(AController* NewController)
{
	// 调用父类的PossessedBy实现
	// 确保基础的接管逻辑被正确执行
	Super::PossessedBy(NewController);

	// 检查能力系统组件是否有效
	// 如果有效则初始化能力系统的Actor信息
	if (WarriorAbilitySystemComponent)
	{
		// 初始化能力系统的Actor信息
		// 第一个this: 拥有能力系统的Actor（这个战士角色）
		// 第二个this: 实际的Avatar（同样是这个战士角色）
		// 在某些情况下，拥有者和Avatar可能是不同的Actor
		//为什么可能不同，其实就是 人与工具的关系，人催动工具，使用的是工具的技能

		WarriorAbilitySystemComponent->InitAbilityActorInfo(this, this);
		//如果人物没有设置 默认的初始Data 就提示 
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forget to assign start up data to %s"), *GetName());
	}
}

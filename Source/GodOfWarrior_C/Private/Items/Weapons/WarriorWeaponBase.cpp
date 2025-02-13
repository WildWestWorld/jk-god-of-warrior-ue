// Jackie Lee .All Rights Reserved


#include "Items/Weapons/WarriorWeaponBase.h"

#include "Components/BoxComponent.h"

// Sets default values
AWarriorWeaponBase::AWarriorWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 创建武器的静态网格体组件，并命名为"WeaponMesh"
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	// 将WeaponMesh设置为根组件，这样其他组件可以依附于它
	SetRootComponent(WeaponMesh);

	// 创建武器的碰撞盒组件，并命名为"WeaponCollisionBox"
	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	// 将碰撞盒附加到根组件(WeaponMesh)上，使其跟随武器模型移动
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	// 设置碰撞盒的大小为一个20单位的立方体(x=20,y=20,z=20)
	//这个是默认值，后面我我们创建蓝图 的时候可以修改
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	// 初始时禁用碰撞检测，可以在需要时（如攻击时）动态开启
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

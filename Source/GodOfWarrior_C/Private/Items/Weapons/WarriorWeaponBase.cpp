// Jackie Lee .All Rights Reserved

#include "Items/Weapons/WarriorWeaponBase.h"

#include "Components/BoxComponent.h"
#include "Debug/WarriorDebugHelper.h"

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
	// 这个是默认值，后面我我们创建蓝图 的时候可以修改
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	// 初始时禁用碰撞检测，可以在需要时（如攻击时）动态开启
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

// 当武器的碰撞盒开始与其他物体重叠时调用此函数
// @param OverlappedComponent - 发生重叠的组件（此处为武器的碰撞盒）
// @param OtherActor - 与武器碰撞的其他角色
// @param OtherComp - 其他角色的碰撞组件
// @param OtherBodyIndex - 物理模拟体的索引
// @param bFromSweep - 是否由扫描产生的重叠
// @param SweepResult - 扫描的结果数据
void AWarriorWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                    bool bFromSweep, const FHitResult& SweepResult)
{
	// 获取武器所属的Pawn
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	// 确保武器已被正确分配给一个Pawn，否则报错
	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn for the weapon:%s"), *GetName())
	// 尝试将碰撞的Actor转换为Pawn类型
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		// 确保不是与武器持有者自己发生碰撞
		if (WeaponOwningPawn != HitPawn)
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
	}
}

// 当武器的碰撞盒结束与其他物体重叠时调用此函数
// @param OverlappedComponent - 结束重叠的组件（此处为武器的碰撞盒）
// @param OtherActor - 与武器结束碰撞的其他角色
// @param OtherComp - 其他角色的碰撞组件
// @param OtherBodyIndex - 物理模拟体的索引
void AWarriorWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 获取武器所属的Pawn
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	// 确保武器已被正确分配给一个Pawn，否则报错
	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn for the weapon:%s"), *GetName())
	// 尝试将碰撞的Actor转换为Pawn类型
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		// 确保不是与武器持有者自己发生碰撞
		if (WeaponOwningPawn != HitPawn)
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}

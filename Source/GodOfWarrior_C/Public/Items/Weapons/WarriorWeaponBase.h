// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorWeaponBase.generated.h"

// 前向声明UBoxComponent类,用于减少头文件依赖
class UBoxComponent;

// 声明一个委托,用于处理武器与目标交互的事件
// 该委托接受一个AActor*参数,用于传递交互的目标对象
DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*);

/**
 * 战士武器基类
 * 所有具体武器类型都应该继承自这个基类
 * 提供了基础的武器功能,如碰撞检测、网格体显示等
 */
UCLASS()
class GODOFWARRIOR_C_API AWarriorWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * 构造函数
	 * 用于设置该Actor的默认属性值
	 * 初始化武器的基础组件
	 */
	AWarriorWeaponBase();

	// 当武器击中目标时触发的委托
	FOnTargetInteractedDelegate OnWeaponHitTarget;
	// 当武器从目标抽离时触发的委托
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget;

protected:
	/** 
	 * 武器的静态网格体组件
	 * 用于表现武器的3D模型
	 * 可在蓝图中查看和编辑,但不能在其他类中直接访问
	 * VisibleAnywhere - 在所有属性窗口中可见
	 * BlueprintReadOnly - 蓝图中只读
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	UStaticMeshComponent* WeaponMesh;

	/**
	 * 武器的碰撞盒组件
	 * 用于检测武器与其他物体的碰撞
	 * 可在蓝图中查看和编辑,但不能在其他类中直接访问
	 * 主要用于实现武器的伤害判定
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	UBoxComponent* WeaponCollisionBox;

	/**
	 * 武器碰撞盒开始重叠时的回调函数
	 * 当武器与其他物体开始接触时会被自动调用
	 * @param OverlappedComponent - 发生重叠的组件(本例中是武器的碰撞盒)
	 * @param OtherActor - 与武器碰撞的其他Actor
	 * @param OtherComp - 与武器碰撞的其他组件
	 * @param OtherBodyIndex - 其他碰撞体的索引
	 * @param bFromSweep - 是否是扫掠检测触发的重叠
	 * @param SweepResult - 扫掠检测的结果数据
	 */
	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                                        bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * 武器碰撞盒结束重叠时的回调函数
	 * 当武器与其他物体结束接触时会被自动调用
	 * @param OverlappedComponent - 结束重叠的组件(本例中是武器的碰撞盒)
	 * @param OtherActor - 与武器结束碰撞的其他Actor
	 * @param OtherComp - 与武器结束碰撞的其他组件
	 * @param OtherBodyIndex - 其他碰撞体的索引
	 */
	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	/**
	 * 获取武器碰撞盒的内联函数
	 * 提供对武器碰撞盒的访问接口
	 * @return 返回武器的碰撞盒组件指针
	 * FORCEINLINE确保这个函数会被内联,提高性能
	 * const表示这个函数不会修改类的成员变量
	 */
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};

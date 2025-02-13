// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorWeaponBase.generated.h"

// 前向声明UBoxComponent类
class UBoxComponent;

/**
 * 战士武器基类
 * 所有具体武器类型都应该继承自这个基类
 */
UCLASS()
class GODOFWARRIOR_C_API AWarriorWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * 构造函数
	 * 用于设置该Actor的默认属性值
	 */
	AWarriorWeaponBase();

protected:
	/** 
	 * 武器的静态网格体组件
	 * 用于表现武器的3D模型
	 * 可在蓝图中查看和编辑，但不能在其他类中直接访问
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	UStaticMeshComponent* WeaponMesh;

	/**
	 * 武器的碰撞盒组件
	 * 用于检测武器与其他物体的碰撞
	 * 可在蓝图中查看和编辑，但不能在其他类中直接访问
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	UBoxComponent* WeaponCollisionBox;

public:
	/**
	 * 获取武器碰撞盒的内联函数
	 * @return 返回武器的碰撞盒组件指针
	 * FORCEINLINE确保这个函数会被内联，提高性能
	 */
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};

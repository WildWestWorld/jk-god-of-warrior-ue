// Jackie Lee .All Rgihts Reserved

/**
* 代码逻辑说明:
* 1. 这是一个基础角色类，实现了能力系统接口(IAbilitySystemInterface)
* 2. 主要功能：
*    - 管理角色的能力系统组件
*    - 管理角色的属性集
*    - 处理角色被控制时的初始化
*    - 提供能力系统相关组件的访问接口
* 3. 继承关系：
*    - 继承自UE的Character基类
*    - 实现能力系统接口以支持GAS功能
*/

#pragma once

// 能力系统接口头文件，来自Gameplay Ability插件
#include "AbilitySystemInterface.h"

#include "CoreMinimal.h"
#include "Components/Pawn/Combat/PawnCombatComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "WarriorBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UWarriorAttributeSet;
class UWarriorAbilitySystemComponent;
class UMotionWarpingComponent;

/**
* 战士基础角色类
* 实现了能力系统接口，用于管理角色的能力和属性
* IPawnCombatInterface 是我们自己写的类
* IPawnUIInterface 是我们自己写的类
*/
UCLASS()
class GODOFWARRIOR_C_API AWarriorBaseCharacter : public ACharacter, public IAbilitySystemInterface,
                                                 public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	/** 构造函数，设置角色的默认属性值 */
	AWarriorBaseCharacter();

	/**
	 * 实现自IAbilitySystemInterface的接口方法
	 * 必须实现此方法以返回角色的能力系统组件
	 * @return 返回角色的能力系统组件实例
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//来自于IPawnCombatInterface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//来自于IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;

protected:
	/**
	 * 重写自APawn的生命周期函数
	 * 当角色被Controller接管控制权时调用
	 * @param NewController - 接管控制的Controller实例
	 */
	virtual void PossessedBy(AController* NewController) override;

	/**
	 * 角色的能力系统组件
	 * 需要启用Gameplay Ability System插件才能使用
	 * 负责管理角色的所有能力相关功能
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	UWarriorAbilitySystemComponent* WarriorAbilitySystemComponent;

	/**
	 * 角色的属性集合
	 * 包含角色的各种基础属性（如生命值、魔法值等）
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	UWarriorAttributeSet* WarriorAttributeSet;


	/**
	 * 角色启动数据资产引用
	 * 使用TSoftObjectPtr以支持异步加载 ，软链接 异步加载
	 * 包含角色初始化时需要的各种数据
	 * UDataAsset_StartUpDataBase  放的就是 各种Ability
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

public:
	/**
	 * 获取角色能力系统组件的内联函数
	 * 使用FORCEINLINE强制内联以优化性能
	 * @return 返回角色的能力系统组件实例
	 */
	FORCEINLINE UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const
	{
		return WarriorAbilitySystemComponent;
	}

	/**
	 * 获取角色属性集的内联函数
	 * @return 返回角色的属性集实例
	 */
	FORCEINLINE UWarriorAttributeSet* GetWarriorAttribute() const { return WarriorAttributeSet; }
};

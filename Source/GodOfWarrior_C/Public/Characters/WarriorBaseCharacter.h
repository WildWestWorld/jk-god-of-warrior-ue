// Jackie Lee .All Rgihts Reserved

#pragma once


//来自于 Gameplay Ability插件 (写入类型IAbilitySystemInterface不会有代码提示，得自己查询导入)
#include "AbilitySystemInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WarriorBaseCharacter.generated.h"


class UWarriorAttributeSet;
class UWarriorAbilitySystemComponent;

UCLASS()
class GODOFWARRIOR_C_API AWarriorBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarriorBaseCharacter();

	//方法 来自 IAbilitySystemInterface 继承IAbilitySystemInterface 必须实现,需要返回UWarriorAbilitySystemComponent 类型  不然报错
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	//生命周期 来自 APawn
	//开始控制该角色的时候
	virtual void PossessedBy(AController* NewController) override;

	//能力组件
	//UWarriorAbilitySystemComponent 是我们自己创建的组件，创建此组件需要 开启Ability System插件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	UWarriorAbilitySystemComponent* WarriorAbilitySystemComponent;
	//人物属性集合
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	UWarriorAttributeSet* WarriorAttributeSet;

public:
	// 	什么是内联(Inline)：
	// 内联是一种编译器优化技术
	// 当函数被调用时，编译器会直接将函数的代码插入到调用处，而不是进行普通的函数调用
	// 这样可以避免函数调用的开销(比如压栈、跳转、返回等操作)
	//FORCEINLINE 强制内联
	//这里是用于获取我们的能力组件 和人物属性集合的
	//因为在蓝图中是只读的，所以我们在这里写个public接口 这样这别的地方也可以拿到
	FORCEINLINE UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const
	{
		return WarriorAbilitySystemComponent;
	}

	FORCEINLINE UWarriorAttributeSet* GetWarriorAttribute() const { return WarriorAttributeSet; }
};

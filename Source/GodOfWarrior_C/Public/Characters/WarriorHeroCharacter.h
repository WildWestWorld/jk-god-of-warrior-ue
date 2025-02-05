// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorHeroCharacter.generated.h"


// class
class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class GODOFWARRIOR_C_API AWarriorHeroCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()

public:
	// init
	AWarriorHeroCharacter();
	
	
protected:
	// protected：这个访问修饰符表示 BeginPlay 函数只能在类内部以及派生类中访问，外部不能访问。
	// virtual：这个关键字表示该函数是虚函数，派生类可以覆盖（重写）它。
	// void：表示该函数没有返回值。
	// BeginPlay()：这是函数名，表示在 Actor 创建时或游戏开始时调用的函数。
	// override：表示你正在重写基类中的 BeginPlay 函数。如果基类中没有这个函数或签名不匹配，编译器会给出错误提示。
	//生命周期函数
	virtual void BeginPlay() override;

private:
#pragma region Components
	// 	VisibleAnywhere：表示这个属性在编辑器的所有地方都可以看到，但它是只读的（不能编辑）。它表示你在 UE4 编辑器中会看到这个变量，但是不能修改它。
	// BlueprintReadOnly：表示这个属性在蓝图中可以读取，但不能修改。在蓝图中使用时，它是只读的。
	// Category="Camera"：将这个属性分类到 “Camera” 这一组。这样在编辑器中，属性会被归类在 "Camera" 类目下。
	// meta=(AllowPrivateAccess=true)：这是一个元数据属性，表示即使 CameraBoom 是 private，它仍然可以通过反射机制在编辑器或蓝图中访问。
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess=true))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess=true))
	UCameraComponent* FollowCamera;
#pragma endregion Components
};

// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

/**
 * GodOfWarrior_C模块的构建规则类
 * 用于配置项目的编译和依赖关系
 */
public class GodOfWarrior_C : ModuleRules
{
	public GodOfWarrior_C(ReadOnlyTargetRules Target) : base(Target)
	{
		// 设置预编译头文件的使用模式
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// 添加公共依赖模块

		// 你在 PublicDependencyModuleNames.AddRange 中添加了 "GameplayTags"，
		// 这意味着你的项目现在依赖于 Unreal Engine 的 游戏标签系统 模块（GameplayTags）。游戏标签系统是 Unreal Engine 提供的一种机制，
		// 用于管理和处理游戏中各种事件、状态、对象或其他元素的标签。

		// 		举个例子：
		// 		假设你需要管理角色的状态，比如角色是否正在攻击，你可以定义一个标签 Character.IsAttacking，然后在不同的系统中根据这个标签做出相应的行为。
		// 定义游戏标签
		// 		UE_DEFINE_GAMEPLAY_TAG(AttackTag, "Character.IsAttacking");
		// 监听角色攻击状态
		// 		if (MyCharacter.HasTag(AttackTag))
		// 		{
		// 			// 角色正在攻击
		// 		}
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", // 核心功能
			"CoreUObject", // 核心对象系统
			"Engine", // 引擎功能
			"InputCore", // 输入系统
			"EnhancedInput", // 增强输入系统
			"GameplayTags", // 游戏标签系统
			"GameplayTasks", "GameplayAbilities", "AIModule", //开启GAS得加入
			"AnimGraphRuntime", //特殊動畫需要开启
			"MotionWarping" //移动扭曲
		});


		// 添加私有依赖模块
		PrivateDependencyModuleNames.AddRange(new string[] { });


		// 只在 Editor 模式下加载 BlueprintAssist
		if (Target.Type == TargetType.Editor)
		{
			PrivateDependencyModuleNames.Add("BlueprintAssist");
		}

		// 如果需要使用Slate UI，取消下面的注释
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// 如果需要使用在线功能，取消下面的注释
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// 要包含Steam在线子系统，需要在uproject文件的plugins部分添加它，并将Enabled属性设置为true
	}
}
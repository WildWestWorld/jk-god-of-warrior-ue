// Jackie Lee .All Rights Reserved


#include "AnimInstances/Hero/WarriorHeroLinkedAnimLayer.h"

#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"

/**
 * 获取英雄角色动画实例
 * 该函数通过以下步骤获取动画实例:
 * 1. 使用GetOwningComponent()获取拥有该动画层的骨骼网格体组件
 * 2. 调用GetAnimInstance()获取骨骼网格体当前的动画实例
 * 3. 使用Cast将获取的动画实例转换为UWarriorHeroAnimInstance类型
 * 
 * @return 返回转换后的英雄角色动画实例指针，如果转换失败则返回nullptr
 */
UWarriorHeroAnimInstance* UWarriorHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UWarriorHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

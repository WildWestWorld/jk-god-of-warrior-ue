#pragma once

/**
 * 确认类型枚举
 * 用于表示确认结果的两种状态
 */
UENUM()
enum class EWarriorConfirmType : uint8
{
	Yes, // 确认/是
	No // 否定/否
};

UENUM()
enum class EWarriorValidType : uint8
{
	Valid,
	Invalid,
};

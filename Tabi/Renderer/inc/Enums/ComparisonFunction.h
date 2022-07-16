#pragma once

namespace tabi
{
	enum class EComparisonFunction : uint8_t
	{
		Never,
		Less,
		Equal,
		LessOrEqual,
		Greater,
		GreaterOrEqual,
		NotEqual,
		Always
	};
}

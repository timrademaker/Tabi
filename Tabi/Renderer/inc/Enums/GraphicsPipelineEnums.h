#pragma once

#include <TabiMacros.h>

namespace tabi
{
	enum class EToplolgy : uint8_t
	{
		Point,
		Line,
		LineStrip,
		Triangle,
		TriangleStrip,
	};

	enum class EBlendFactor : uint8_t
	{
		Zero,
		One,
		SrcAlpha,
		DstAlpha,
		InvSrcAlpha,
		InvDstAlpha,
		SrcColor,
		DstColor,
		InvSrcColor,
		InvDstColor
	};

	enum class EBlendOperation : uint8_t
	{
		Add,
		Subtract,
		ReverseSubtract,
		Min,
		Max
	};

	enum class EPolygonMode : uint8_t
	{
		Point,
		Line,
		Fill
	};

	enum class ECullMode : uint8_t
	{
		None,
		Front,
		Back
	};

	enum class EColorMask : uint8_t
	{
		None = 0,
		Red = 1 << 0,
		Green = 1 << 1,
		Blue = 1 << 2,
		Alpha = 1 << 3,
		All = Red | Green | Blue | Alpha
	};
	TABI_ENUM_FLAG(EColorMask);

	enum class EStencilOperation : uint8_t
	{
		Zero,
		Keep,
		Replace,
		Increment,
		Decrement,
		Invert,
		IncrementWrap,
		DecrementWrap
	};
}

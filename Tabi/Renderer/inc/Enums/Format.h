#pragma once

#include <cstdint>

namespace tabi
{
	// https://docs.microsoft.com/en-us/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format
	enum class EFormat : uint8_t
	{
		Unknown,

		/* 32 bit */
		RGBA32_float,
		RGBA32_uint,
		RGBA32_sint,

		RGB32_float,
		RGB32_uint,
		RGB32_sint,

		RG32_float,
		RG32_uint,
		RG32_sint,

		R32_float,
		R32_uint,
		R32_sint,

		/* 16 bit */
		RGBA16_float,
		RGBA16_unorm,
		RGBA16_snorm,
		RGBA16_uint,
		RGBA16_sint,

		RGB16_float,
		RGB16_unorm,
		RGB16_snorm,
		RGB16_uint,
		RGB16_sint,

		RG16_float,
		RG16_unorm,
		RG16_snorm,
		RG16_uint,
		RG16_sint,

		R16_float,
		R16_unorm,
		R16_snorm,
		R16_uint,
		R16_sint,

		/* 8  bit */
		RGBA8_unorm,
		RGBA8_snorm,
		RGBA8_uint,
		RGBA8_sint,

		RGB8_unorm,
		RGB8_snorm,
		RGB8_uint,
		RGB8_sint,

		RG8_unorm,
		RG8_snorm,
		RG8_uint,
		RG8_sint,

		R8_unorm,
		R8_snorm,
		R8_uint,
		R8_sint,

		/* Depth */
		Depth16,
		Depth24,
		Depth32_float,

		Depth24Stencil8,

		// TODO: Some whacky formats (and compressed formats?)

		Count
	};
}

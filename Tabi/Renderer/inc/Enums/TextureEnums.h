#pragma once

#include <cstdint>

namespace tabi
{
	enum class ETextureDimension : uint8_t
	{
		Unknown,
		Buffer,
		Tex1D,
		Tex1DArray,
		Tex2D,
		Tex2DArray,
		Tex3D,
		CubeMap,
		CubeMapArray
	};

	enum class ETextureRole : uint8_t
	{
		// Texture used as... texture
		Texture,
		// Texture used as depth-stencil buffer
		DepthStencil,
		// Texture used as render target
		RenderTexture
	};
}

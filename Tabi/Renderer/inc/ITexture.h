#pragma once

#include "Format.h"

namespace tabi
{
	enum class ETextureDimension : uint8_t
	{
		Buffer,	// TODO: Should this be a thing? Isn't 1D basically the same?
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
		Texture,		// Texture used as... texture
		DepthStencil,	// Texture used as depth-stencil buffer
		RenderTexture	// Texture used as render target
	};

	// https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_resource_desc
	struct TextureDescription
	{
		ETextureDimension m_Dimension = ETextureDimension::Tex2D;
		ETextureRole m_Role = ETextureRole::Texture;
		EFormat m_Format = EFormat::RGBA32_uint;
		// Use (where can this texture be accessed from?)	(https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ne-d3d12-d3d12_resource_flags)
		// OGL doesn't care about that though, so maybe leave it out for now
		uint64_t m_Width = 0;
		uint64_t m_Height = 0;
		uint16_t m_Depth = 0;	// Depth if 3D texture, array size if array type
		uint16_t m_MipLevels = 1;
	};

	// TODO: Not much of an interface. Should this just be Texture (or BaseTexture or TextureHandle)?
	class ITexture
	{

	};
}
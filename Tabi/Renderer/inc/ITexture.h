#pragma once

#include "Format.h"

namespace tabi
{
	enum class ETextureDimension : uint8_t
	{
		Unknown,
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
		// Texture used as... texture
		Texture,
		// Texture used as depth-stencil buffer
		DepthStencil,
		// Texture used as render target
		RenderTexture
	};

	// https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_resource_desc
	struct TextureDescription
	{
		ETextureDimension m_Dimension = ETextureDimension::Unknown;
		ETextureRole m_Role = ETextureRole::Texture;
		EFormat m_Format = EFormat::Unknown;
		uint64_t m_Width = 0;
		uint64_t m_Height = 0;
		uint16_t m_Depth = 0;	// Depth if 3D texture, array size if array type
		uint16_t m_MipLevels = 1;
	};

	// TODO: Not much of an interface. Should this just be Texture (or BaseTexture or TextureHandle)?
	class ITexture
	{
	public:
		inline ETextureDimension GetTextureDimension() const
		{
			return m_TextureDimension;
		}

		inline EFormat GetTextureFormat() const
		{
			return m_Format;
		}

	protected:
		ITexture(ETextureDimension a_TextureDimension, EFormat a_TextureFormat)
			: m_TextureDimension(a_TextureDimension), m_Format(a_TextureFormat)
		{};

	private:
		ETextureDimension m_TextureDimension = ETextureDimension::Unknown;
		EFormat m_Format = EFormat::Unknown;
	};
}

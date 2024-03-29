#pragma once

#include "Enums/Format.h"
#include "Enums/TextureEnums.h"

#include <TabiMacros.h>

#include <cstdint>

namespace tabi
{
	// https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_resource_desc
	struct TextureDescription
	{
		ETextureDimension m_Dimension = ETextureDimension::Unknown;
		ETextureRole m_Role = ETextureRole::Texture;
		EFormat m_Format = EFormat::Unknown;
		uint64_t m_Width = 0;
		uint64_t m_Height = 0;
		// Depth if 3D texture, array size if m_Dimension is an array type
		uint16_t m_Depth = 0;
		uint16_t m_MipLevels = 1;
	};

	class Texture
	{
	public:
		TABI_NO_COPY(Texture);
		TABI_NO_MOVE(Texture);

		inline const TextureDescription& GetTextureDescription() const
		{
			return m_TextureDescription;
		}

	protected:
		Texture(const TextureDescription& a_TextureDescription)
			: m_TextureDescription(a_TextureDescription)
		{}
		~Texture() = default;

	private:
		TextureDescription m_TextureDescription;
	};
}

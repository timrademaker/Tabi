#pragma once

#include "Enums/TextureEnums.h"

namespace tabi
{
	struct TextureUpdateDescription
	{
		// The data to copy to the texture
		const void* m_Data = nullptr;

		// The amount of data to copy in the X direction of the texture
		uint32_t m_DataWidth = 0;
		// The amount of data to copy in the Y direction of the texture
		uint32_t m_DataHeight = 0;
		// The amount of data to copy in the Z direction of the texture, or the number of layers to copy to a texture array
		uint32_t m_DataDepth = 0;

		// The offset in the X direction within the texture at which to start replacing the existing data
		uint32_t m_OffsetX = 0;
		// The offset in the Y direction within the texture at which to start replacing the existing data
		uint32_t m_OffsetY = 0;
		// The offset in the Z direction within the texture at which to start replacing the existing data, or the index into a texture array
		uint32_t m_OffsetZ = 0;

		// The cube map face to update if the texture is a cube map
		ECubeMapFace m_CubeFace = ECubeMapFace::XPositive;

		// The index of the mipmap level to update
		uint16_t m_MipLevel = 0;
	};
}

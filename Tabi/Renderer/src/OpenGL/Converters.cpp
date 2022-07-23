#include "OpenGL/Converters.h"

#include "Texture.h"

#include <TabiMacros.h>

namespace tabi
{
		GLenum GLTextureDimension(tabi::ETextureDimension a_Dimension)
		{
			switch (a_Dimension)
			{
			case tabi::ETextureDimension::Buffer: 
				return GL_TEXTURE_BUFFER;
			case tabi::ETextureDimension::Tex1D:
				return GL_TEXTURE_1D;
			case tabi::ETextureDimension::Tex1DArray:
				return GL_TEXTURE_1D_ARRAY;
			case tabi::ETextureDimension::Tex2D:
				return GL_TEXTURE_2D;
			case tabi::ETextureDimension::Tex2DArray:
				return GL_TEXTURE_2D_ARRAY;
			case tabi::ETextureDimension::Tex3D:
				return GL_TEXTURE_3D;
			case tabi::ETextureDimension::CubeMap:
				return GL_TEXTURE_CUBE_MAP;
			case tabi::ETextureDimension::CubeMapArray:
				return GL_TEXTURE_CUBE_MAP_ARRAY;
			}

			TABI_ASSERT(false, "Unknown texture dimension");
			return GL_INVALID_ENUM;
		}

		GLenum GLShaderType(EShaderType a_ShaderType)
		{
			switch (a_ShaderType)
			{
			case EShaderType::Vertex:
				return GL_VERTEX_SHADER;
			case EShaderType::Pixel:
				return GL_FRAGMENT_SHADER;
			case EShaderType::Compute:
				return GL_COMPUTE_SHADER;
			}

			TABI_ASSERT(false, "Unknown shader type");
			return GL_INVALID_ENUM;
		}
}
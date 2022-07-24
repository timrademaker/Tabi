#include "OpenGL/Converters.h"

#include "Texture.h"

#include <TabiMacros.h>

namespace tabi
{
		GLenum GLTextureDimension(tabi::ETextureDimension a_Dimension)
		{
			switch (a_Dimension)
			{
			case ETextureDimension::Buffer:
				return GL_TEXTURE_BUFFER;
			case ETextureDimension::Tex1D:
				return GL_TEXTURE_1D;
			case ETextureDimension::Tex1DArray:
				return GL_TEXTURE_1D_ARRAY;
			case ETextureDimension::Tex2D:
				return GL_TEXTURE_2D;
			case ETextureDimension::Tex2DArray:
				return GL_TEXTURE_2D_ARRAY;
			case ETextureDimension::Tex3D:
				return GL_TEXTURE_3D;
			case ETextureDimension::CubeMap:
				return GL_TEXTURE_CUBE_MAP;
			case ETextureDimension::CubeMapArray:
				return GL_TEXTURE_CUBE_MAP_ARRAY;

			case ETextureDimension::Unknown:
			default:
				TABI_ASSERT(false, "Unknown texture dimension");
				return GL_INVALID_ENUM;
			}
		}

		GLenum GLFormat(EFormat a_Format)
		{
			switch(a_Format)
			{
			case EFormat::RGBA32_float:
			case EFormat::RGBA32_uint:
			case EFormat::RGBA32_sint:
			case EFormat::RGBA16_float:
			case EFormat::RGBA16_unorm:
			case EFormat::RGBA16_snorm:
			case EFormat::RGBA16_uint:
			case EFormat::RGBA16_sint:
			case EFormat::RGBA8_unorm:
			case EFormat::RGBA8_snorm:
			case EFormat::RGBA8_uint:
			case EFormat::RGBA8_sint:
				return GL_RGBA;

			case EFormat::RGB32_float:
			case EFormat::RGB32_uint:
			case EFormat::RGB32_sint:
			case EFormat::RGB16_float:
			case EFormat::RGB16_unorm:
			case EFormat::RGB16_snorm:
			case EFormat::RGB16_uint:
			case EFormat::RGB16_sint:
			case EFormat::RGB8_unorm:
			case EFormat::RGB8_snorm:
			case EFormat::RGB8_uint:
			case EFormat::RGB8_sint:
				return GL_RGB;

			case EFormat::RG32_float:
			case EFormat::RG32_uint:
			case EFormat::RG32_sint:
			case EFormat::RG16_float:
			case EFormat::RG16_unorm:
			case EFormat::RG16_snorm:
			case EFormat::RG16_uint:
			case EFormat::RG16_sint:
			case EFormat::RG8_unorm:
			case EFormat::RG8_snorm:
			case EFormat::RG8_uint:
			case EFormat::RG8_sint:
				return GL_RG;

			case EFormat::R32_float:
			case EFormat::R32_uint:
			case EFormat::R32_sint:
			case EFormat::R16_float:
			case EFormat::R16_unorm:
			case EFormat::R16_snorm:
			case EFormat::R16_uint:
			case EFormat::R16_sint:
			case EFormat::R8_unorm:
			case EFormat::R8_snorm:
			case EFormat::R8_uint:
			case EFormat::R8_sint:
				return GL_RED;

			case EFormat::Depth16:
			case EFormat::Depth24:
			case EFormat::Depth32_float:
				return  GL_DEPTH_COMPONENT;

			case EFormat::Depth24Stencil8:
				return GL_DEPTH_STENCIL;

			case EFormat::Unknown:
			default:
				TABI_ASSERT(false, "Unknown texture format");
				return GL_INVALID_ENUM;
			}
		}

		GLenum GLInternalFormat(EFormat a_Format)
		{
			switch (a_Format)
			{
			case EFormat::RGBA32_float:
				return GL_RGBA32F;
			case EFormat::RGBA32_uint:
				return GL_RGBA32UI;
			case EFormat::RGBA32_sint:
				return GL_RGBA32I;
			case EFormat::RGB32_float:
				return GL_RGB32F;
			case EFormat::RGB32_uint:
				return GL_RGB32UI;
			case EFormat::RGB32_sint:
				return GL_RGB32I;
			case EFormat::RG32_float:
				return GL_RG32F;
			case EFormat::RG32_uint:
				return GL_RG32UI;
			case EFormat::RG32_sint:
				return GL_RG32I;
			case EFormat::R32_float:
				return GL_R32F;
			case EFormat::R32_uint:
				return GL_R32UI;
			case EFormat::R32_sint:
				return GL_R32I;
			case EFormat::RGBA16_float:
				return GL_RGBA16F;
			case EFormat::RGBA16_unorm:
				return GL_RGBA16;
			case EFormat::RGBA16_snorm:
				return GL_RGBA16_SNORM;
			case EFormat::RGBA16_uint:
				return GL_RGBA16F;
			case EFormat::RGBA16_sint:
				return GL_RGBA16I;
			case EFormat::RGB16_float:
				return GL_RGB16F;
			case EFormat::RGB16_unorm:
				return GL_RGB16;
			case EFormat::RGB16_snorm:
				return GL_RGB16_SNORM;
			case EFormat::RGB16_uint:
				return GL_RGB16UI;
			case EFormat::RGB16_sint:
				return GL_RGB16I;
			case EFormat::RG16_float:
				return GL_RG16F;
			case EFormat::RG16_unorm:
				return GL_RG16;
			case EFormat::RG16_snorm:
				return GL_RG16_SNORM;
			case EFormat::RG16_uint:
				return GL_RG16UI;
			case EFormat::RG16_sint:
				return GL_RG16I;
			case EFormat::R16_float:
				return GL_R16F;
			case EFormat::R16_unorm:
				return GL_R16;
			case EFormat::R16_snorm:
				return GL_R16_SNORM;
			case EFormat::R16_uint:
				return GL_R16UI;
			case EFormat::R16_sint:
				return GL_R16I;
			case EFormat::RGBA8_unorm:
				return GL_RGBA8;
			case EFormat::RGBA8_snorm:
				return GL_RGBA8_SNORM;
			case EFormat::RGBA8_uint:
				return GL_RGBA8UI;
			case EFormat::RGBA8_sint:
				return GL_RGBA8I;
			case EFormat::RGB8_unorm:
				return GL_RGB8;
			case EFormat::RGB8_snorm:
				return GL_RGB8_SNORM;
			case EFormat::RGB8_uint:
				return GL_RGB8UI;
			case EFormat::RGB8_sint:
				return GL_RGB8I;
			case EFormat::RG8_unorm:
				return GL_RGB8;
			case EFormat::RG8_snorm:
				return GL_RGB8_SNORM;
			case EFormat::RG8_uint:
				return GL_RGB8UI;
			case EFormat::RG8_sint:
				return GL_RGB8I;
			case EFormat::R8_unorm:
				return GL_R8;
			case EFormat::R8_snorm:
				return GL_R8_SNORM;
			case EFormat::R8_uint:
				return GL_R8UI;
			case EFormat::R8_sint:
				return GL_R8I;
			case EFormat::Depth16:
				return GL_DEPTH_COMPONENT16;
			case EFormat::Depth24:
				return GL_DEPTH_COMPONENT24;
			case EFormat::Depth32_float:
				return GL_DEPTH_COMPONENT32F;
			case EFormat::Depth24Stencil8:
				return GL_DEPTH24_STENCIL8;

			case EFormat::Unknown:
			default:
				TABI_ASSERT(false, "Unknown internal format");
				return GL_INVALID_ENUM;
			}
		}

		GLenum GLType(EFormat a_Format)
		{
			switch(a_Format)
			{
			case EFormat::RGBA32_float:
			case EFormat::RGB32_float:
			case EFormat::RG32_float:
			case EFormat::R32_float:
			case EFormat::Depth32_float:
			case EFormat::RGBA16_float:
			case EFormat::RGB16_float:
			case EFormat::RG16_float:
			case EFormat::R16_float:
				return GL_FLOAT;

			case EFormat::RGBA32_uint:
			case EFormat::RGB32_uint:
			case EFormat::RG32_uint:
			case EFormat::R32_uint:
				return GL_UNSIGNED_INT;

			case EFormat::RGBA16_unorm:
			case EFormat::RGBA16_uint:
			case EFormat::RGB16_unorm:
			case EFormat::RGB16_uint:
			case EFormat::RG16_unorm:
			case EFormat::RG16_uint:
			case EFormat::R16_unorm:
			case EFormat::R16_uint:
				return GL_UNSIGNED_SHORT;

			case EFormat::RGBA8_unorm:
			case EFormat::RGBA8_uint:
			case EFormat::RGB8_unorm:
			case EFormat::RGB8_uint:
			case EFormat::RG8_unorm:
			case EFormat::RG8_uint:
			case EFormat::R8_unorm:
			case EFormat::R8_uint:
				return GL_UNSIGNED_BYTE;

			case EFormat::RGBA32_sint:
			case EFormat::RGB32_sint:
			case EFormat::RG32_sint:
			case EFormat::R32_sint:
				return GL_INT;

			case EFormat::RGBA16_snorm:
			case EFormat::RGBA16_sint:
			case EFormat::RGB16_snorm:
			case EFormat::RGB16_sint:
			case EFormat::RG16_snorm:
			case EFormat::RG16_sint:
			case EFormat::R16_snorm:
			case EFormat::R16_sint:
				return GL_SHORT;

			case EFormat::RGBA8_snorm:
			case EFormat::RGBA8_sint:
			case EFormat::RGB8_snorm:
			case EFormat::RGB8_sint:
			case EFormat::RG8_snorm:
			case EFormat::RG8_sint:
			case EFormat::R8_snorm:
			case EFormat::R8_sint:
				return GL_BYTE;

			case EFormat::Depth16:
				return GL_UNSIGNED_SHORT;
			case EFormat::Depth24:
				return GL_UNSIGNED_INT;

			case EFormat::Depth24Stencil8:
				return GL_UNSIGNED_INT_24_8;

			case EFormat::Unknown:
			default:
				TABI_ASSERT(false, "Unknown data type");
				return GL_INVALID_ENUM;
			}
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

			case EShaderType::Invalid:
			default:
				TABI_ASSERT(false, "Unknown shader type");
				return GL_INVALID_ENUM;
			}
		}

		GLenum GLCubeMapFace(ECubemapFace a_Face)
		{
			switch(a_Face)
			{
			case ECubemapFace::XPositive:
				return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
			case ECubemapFace::XNegative:
				return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
			case ECubemapFace::YPositive:
				return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
			case ECubemapFace::YNegative:
				return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
			case ECubemapFace::ZPositive:
				return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
			case ECubemapFace::ZNegative:
				return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;

			default:
				TABI_ASSERT(false, "Unknown cubemap face");
				return GL_INVALID_ENUM;
			}
		}
}

#include "Resources/TextureResource.h"

#include <IDevice.h>
#include <ICommandList.h>
#include <Texture.h>

#include <Graphics.h>

#include <Logging.h>

#include <tinygltf/tiny_gltf.h>


tabi::shared_ptr<tabi::TextureResource> tabi::TextureResource::LoadTextureFromModel(const tinygltf::Model& a_Model,
                                                                                    const std::size_t a_TextureIndex)
{
    // Texture
    if (a_TextureIndex >= a_Model.textures.size())
    {
        TABI_WARN("Texture index out of bounds!");
        return nullptr;
    }
    
    const std::size_t imageIndex = a_Model.textures[a_TextureIndex].source;
    
    auto tex = tabi::make_shared<TextureResource>();
    
    tex->m_Width = a_Model.images[imageIndex].width;
    tex->m_Height = a_Model.images[imageIndex].height;
    tex->m_Format = ConvertFormat(a_Model.images[imageIndex].component, a_Model.images[imageIndex].bits, a_Model.images[imageIndex].pixel_type);

    tex->m_TextureData = a_Model.images[imageIndex].image;

    tex->m_Texture = tabi::LoadTexture(tex->m_Format, ETextureDimension::Tex2D, tex->m_Width, tex->m_Height, 1, tex->m_TextureData.data());

    // Sampler
    auto& samplerIndex = a_Model.textures[a_TextureIndex].sampler;

    if (samplerIndex != -1)
    {
        auto& sampler = a_Model.samplers[samplerIndex];
        tex->m_SamplerDescription.m_WrapMode = ConvertWrapMode(sampler.wrapS);
        tex->m_SamplerDescription.m_MinFilter = ConvertFilter(sampler.minFilter);
        tex->m_SamplerDescription.m_MagFilter = ConvertFilter(sampler.magFilter);
    }

    return tex;
}

tabi::EWrapMode tabi::TextureResource::ConvertWrapMode(unsigned a_WrapMode)
{
    switch(a_WrapMode)
    {
    case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
		return EWrapMode::Clamp;
    case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
        return EWrapMode::Mirror;
    case TINYGLTF_TEXTURE_WRAP_REPEAT:
        return EWrapMode::Wrap;
    default:
        TABI_ASSERT(false, "Unknown texture wrap mode");
        return EWrapMode::Clamp;
    }
}

tabi::EFilterMode tabi::TextureResource::ConvertFilter(unsigned a_MinFilter)
{
    switch (a_MinFilter)
    {
    case TINYGLTF_TEXTURE_FILTER_LINEAR:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
        return EFilterMode::Linear;
    case TINYGLTF_TEXTURE_FILTER_NEAREST:
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
        return EFilterMode::Nearest;
    default:
        TABI_ASSERT(false, "Unknown filter mode");
        return EFilterMode::Nearest;
    }
}

tabi::EFormat tabi::TextureResource::ConvertFormat(uint8_t a_NumComponents, uint8_t a_BitsPerComponent, int a_PixelType)
{
    switch(a_NumComponents)
    {
    case 1:
    {
        switch (a_BitsPerComponent)
        {
        case 8:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_BYTE)
            {
                return EFormat::R8_snorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
            {
                return EFormat::R8_unorm;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        case 16:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_SHORT)
            {
                return EFormat::R16_snorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
            {
                return EFormat::R16_unorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_FLOAT)
            {
                return EFormat::R16_float;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        case 32:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_INT)
            {
                return EFormat::R32_sint;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
            {
                return EFormat::R32_uint;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_FLOAT)
            {
                return EFormat::R32_float;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        }
    }
    case 2:
    {
        switch (a_BitsPerComponent)
        {
        case 8:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_BYTE)
            {
                return EFormat::RG8_snorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
            {
                return EFormat::RG8_unorm;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        case 16:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_SHORT)
            {
                return EFormat::RG16_snorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
            {
                return EFormat::RG16_unorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_FLOAT)
            {
                return EFormat::RG16_float;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        case 32:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_INT)
            {
                return EFormat::RG32_sint;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
            {
                return EFormat::RG32_uint;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_FLOAT)
            {
                return EFormat::RG32_float;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        }
    }
    case 3:
    {
        switch (a_BitsPerComponent)
        {
        case 8:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_BYTE)
            {
                return EFormat::RGB8_snorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
            {
                return EFormat::RGB8_unorm;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        case 16:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_SHORT)
            {
                return EFormat::RGB16_snorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
            {
                return EFormat::RGB16_unorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_FLOAT)
            {
                return EFormat::RGB16_float;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        case 32:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_INT)
            {
                return EFormat::RGB32_sint;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
            {
                return EFormat::RGB32_uint;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_FLOAT)
            {
                return EFormat::RGB32_float;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        }
    }
    case 4:
    {
        switch (a_BitsPerComponent)
        {
        case 8:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_BYTE)
            {
                return EFormat::RGBA8_snorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
            {
                return EFormat::RGBA8_unorm;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        case 16:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_SHORT)
            {
                return EFormat::RGBA16_snorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
            {
                return EFormat::RGBA16_unorm;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_FLOAT)
            {
                return EFormat::RGBA16_float;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        case 32:
        {
            if (a_PixelType == TINYGLTF_COMPONENT_TYPE_INT)
            {
                return EFormat::RGBA32_sint;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
            {
                return EFormat::RGBA32_uint;
            }
            else if (a_PixelType == TINYGLTF_COMPONENT_TYPE_FLOAT)
            {
                return EFormat::RGBA32_float;
            }
            TABI_ASSERT(false, "Unable to convert format");
            return EFormat::Unknown;
        }
        }
    }
    }

    TABI_ASSERT(false, "Unable to convert format");
    return EFormat::Unknown;
}

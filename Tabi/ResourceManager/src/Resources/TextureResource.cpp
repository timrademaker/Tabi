#include "Resources/TextureResource.h"

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

    tex->m_TextureData = a_Model.images[imageIndex].image;

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

#include "Resources/Texture.h"

#include <tinygltf/tiny_gltf.h>

#include <ISampler.h>

#include <Logging.h>

#include <glad/glad.h>


tabi::shared_ptr<tabi::Texture> tabi::Texture::LoadTextureFromModel(const tinygltf::Model& a_Model,
    const std::size_t a_TextureIndex)
{
    // Texture
    if (a_TextureIndex >= a_Model.textures.size())
    {
        TABI_WARN("Texture index out of bounds!");
        return nullptr;
    }
    
    const std::size_t imageIndex = a_Model.textures[a_TextureIndex].source;
    
    auto tex = tabi::make_shared<Texture>();
    
    tex->m_Width = a_Model.images[imageIndex].width;
    tex->m_Height = a_Model.images[imageIndex].height;

    tex->m_TextureData = a_Model.images[imageIndex].image;

    // Sampler
    auto& samplerIndex = a_Model.textures[a_TextureIndex].sampler;

    if (samplerIndex != -1)
    {
        auto& sampler = a_Model.samplers[samplerIndex];
        EWrap wrapS = ConvertWrapMode(sampler.wrapS);
        EWrap wrapT = ConvertWrapMode(sampler.wrapT);
        EMinFilter minFilter = ConvertMinFilter(sampler.minFilter);
        EMagFilter magFilter = ConvertMagFilter(sampler.magFilter);
        
        tex->m_Sampler = ISampler::CreateSharedSampler(wrapS, wrapT, minFilter, magFilter);
    }

    return tex;
}

tabi::EWrap tabi::Texture::ConvertWrapMode(unsigned a_WrapMode)
{
    EWrap wrap = EWrap::ClampToEdge;
    switch(a_WrapMode)
    {
    case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
    {
        wrap = EWrap::ClampToEdge;
        break;
    }
    case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
    {
        wrap = EWrap::MirroredRepeat;
        break;
    }
    case TINYGLTF_TEXTURE_WRAP_REPEAT:
    {
        wrap = EWrap::Repeat;
        break;
    }
    default:
    {
        break;
    }
    }

    return wrap;
}

tabi::EMinFilter tabi::Texture::ConvertMinFilter(unsigned a_MinFilter)
{
    EMinFilter filter = EMinFilter::Linear;

    switch (a_MinFilter)
    {
    case TINYGLTF_TEXTURE_FILTER_LINEAR:
    {
        filter = EMinFilter::Linear;
        break;
    }
    case TINYGLTF_TEXTURE_FILTER_NEAREST:
    {
        filter = EMinFilter::Nearest;
        break;
    }
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:
    {
        filter = EMinFilter::LinearMipmapLinear;
        break;
    }
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
    {
        filter = EMinFilter::LinearMipmapNearest;
        break;
    }
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
    {
        filter = EMinFilter::NearestMipmapLinear;
        break;
    }
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
    {
        filter = EMinFilter::NearestMipmapNearest;
        break;
    }
    default:
    {
        break;
    }
    }

    return filter;
}

tabi::EMagFilter tabi::Texture::ConvertMagFilter(unsigned a_MagFilter)
{
    EMagFilter filter = EMagFilter::Linear;

    switch (a_MagFilter)
    {
    case TINYGLTF_TEXTURE_FILTER_NEAREST:
    {
        filter = EMagFilter::Nearest;
        break;
    }
    case TINYGLTF_TEXTURE_FILTER_LINEAR:
    {
        filter = EMagFilter::Linear;
        break;
    }
    default:
    {
        break;
    }
    }

    return filter;
}

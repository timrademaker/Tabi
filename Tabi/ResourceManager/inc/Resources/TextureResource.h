#pragma once
#include "../IResource.h"

#include <TabiTypes.h>

#include <Sampler.h>

namespace tinygltf
{
    class Model;
}

namespace tabi
{
    class TextureResource : public IResource
    {
    public:
        static tabi::shared_ptr<TextureResource> LoadTextureFromModel(const tinygltf::Model& a_Model, const std::size_t a_TextureIndex);
        // static tabi::shared_ptr<Texture> LoadTexture(const char* a_FilePath);

    private:
        static EWrapMode ConvertWrapMode(unsigned int a_WrapMode);
        static EFilterMode ConvertFilter(unsigned int a_MinFilter);

    public:
        int m_Width;
        int m_Height;

        tabi::vector<unsigned char> m_TextureData;
        SamplerDescription m_SamplerDescription;
    };
}
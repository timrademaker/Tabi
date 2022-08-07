#pragma once
#include "IResource.h"

#include <TabiTypes.h>

#include <Sampler.h>
#include <Enums/Format.h>

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
        static EFormat ConvertFormat(uint8_t a_NumComponents, uint8_t a_BitsPerComponent, int a_PixelType);

    public:
        int m_Width;
        int m_Height;
        EFormat m_Format = EFormat::Unknown;

        tabi::vector<unsigned char> m_TextureData;
        SamplerDescription m_SamplerDescription;
    };
}

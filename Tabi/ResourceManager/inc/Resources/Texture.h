#pragma once
#include "../IResource.h"

#include <TabiTypes.h>

#include <glad/glad.h>


namespace tinygltf
{
    class Model;
}


namespace tabi
{
    class ISampler;
    enum class EWrap;
    enum class EMinFilter;
    enum class EMagFilter;

    class Texture : public IResource
    {
    public:
        static tabi::shared_ptr<Texture> LoadTextureFromModel(const tinygltf::Model& a_Model, const std::size_t a_TextureIndex);
        // static tabi::shared_ptr<Texture> LoadTexture(const char* a_FilePath);

    private:
        static EWrap ConvertWrapMode(unsigned int a_WrapMode);
        static EMinFilter ConvertMinFilter(unsigned int a_MinFilter);
        static EMagFilter ConvertMagFilter(unsigned int a_MagFilter);

    public:
        int m_Width;
        int m_Height;

        tabi::vector<unsigned char> m_TextureData;
        tabi::shared_ptr<ISampler> m_Sampler;

        GLuint m_TextureHandle;
    };
}
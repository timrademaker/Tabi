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
    class Texture : public IResource
    {
    public:
        static tabi::shared_ptr<Texture> LoadTextureFromModel(const tinygltf::Model& a_Model, const std::size_t a_TextureIndex);
        // static tabi::shared_ptr<Texture> LoadTexture(const char* a_FilePath);

    public:
        int m_Width;
        int m_Height;

        tabi::vector<unsigned char> m_TextureData;

        GLuint m_TextureHandle;
    };
}
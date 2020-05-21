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

    private:
        int m_Width;
        int m_Height;

        GLuint m_TextureHandle;
    };
}
#pragma once
#include "../IResource.h"

#include <TabiTypes.h>


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

        graphics::TextureHandle m_TextureHandle;
    };
}
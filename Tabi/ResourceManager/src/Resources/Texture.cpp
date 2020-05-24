#include "Resources/Texture.h"

#include <tinygltf/tiny_gltf.h>

#include <TabiMacros.h>

#include <glad/glad.h>

tabi::shared_ptr<tabi::Texture> tabi::Texture::LoadTextureFromModel(const tinygltf::Model& a_Model,
    const std::size_t a_TextureIndex)
{
    TABI_UNUSED(a_Model);
    TABI_UNUSED(a_TextureIndex);
    if (a_TextureIndex >= a_Model.textures.size())
    {
        return nullptr;
    }
    
    const std::size_t imageIndex = a_Model.textures[a_TextureIndex].source;
    
    auto tex = tabi::make_shared<Texture>();
    
    tex->m_Width = a_Model.images[imageIndex].width;
    tex->m_Height = a_Model.images[imageIndex].height;

    tex->m_TextureData = a_Model.images[imageIndex].image;
   

    return tex;
}

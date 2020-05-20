#include "Resources/Texture.h"

//#include <tinygltf/tiny_gltf.h>

#include <TabiMacros.h>

#include <glad/glad.h>

tabi::shared_ptr<tabi::Texture> tabi::Texture::LoadTextureFromModel(const tinygltf::Model& a_Model,
    const std::size_t a_TextureIndex)
{
    TABI_UNUSED(a_Model);
    TABI_UNUSED(a_TextureIndex);
    //if (a_TextureIndex >= a_Model.textures.size())
    //{
    //    return nullptr;
    //}
    //
    //const std::size_t imageIndex = a_Model.textures[a_TextureIndex].source;
    //
    //auto tex = tabi::make_shared<Texture>()
    //
    //auto width = a_Model.images[imageIndex].width;
    //auto height = a_Model.images[imageIndex].height;
    //
    //{
    //    // Generate texture
    //    glGenTextures(1, &tex->m_TextureHandle);
    //    glBindTexture(GL_TEXTURE_2D, tex->m_TextureHandle);
    //
    //    // Set texture properties
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    //    // Buffer texture
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(a_Model.images[imageIndex].image[0]));
    //}
    //
    //return tex;
    return nullptr;
}

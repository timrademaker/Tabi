#include "Resources/Material.h"

#include <tinygltf/tiny_gltf.h>



using namespace tabi;

tabi::shared_ptr<Material> Material::LoadMaterial(const tinygltf::Model& a_Model, const std::size_t a_MaterialIndex)
{
    if (a_MaterialIndex >= a_Model.materials.size())
    {
        return nullptr;
    }

    auto& mat = a_Model.materials[a_MaterialIndex];

    auto loadedMaterial = tabi::make_shared<Material>();
    loadedMaterial->m_DoubleSided = mat.doubleSided;
    auto metalicRoughness = tabi::make_unique<MetalicRoughness>();
    auto& baseColor = mat.pbrMetallicRoughness.baseColorFactor;
    metalicRoughness->m_BaseColorFactor = tabi::maths::vec4(
        static_cast<float>(baseColor[0]),
        static_cast<float>(baseColor[1]),
        static_cast<float>(baseColor[2]),
        static_cast<float>(baseColor[3])
    );

    if (mat.pbrMetallicRoughness.baseColorTexture.index != -1)
    {
        metalicRoughness->m_BaseColorTexture = Texture::LoadTextureFromModel(a_Model, mat.pbrMetallicRoughness.baseColorTexture.index);
    }

    if (mat.normalTexture.index != -1)
    {
        loadedMaterial->m_NormalTexture = Texture::LoadTextureFromModel(a_Model, mat.normalTexture.index);
    }

    loadedMaterial->m_MetalicRoughness = std::move(metalicRoughness);

    loadedMaterial->m_Name = tabi::string(mat.name.c_str());

    return loadedMaterial;
}

#pragma once

#include "Texture.h"

#include <TabiTypes.h>

#include <vec4.h>

namespace tinygltf
{
    class Model;
}


namespace tabi
{
    struct MetalicRoughness
    {
        math::vec4 m_BaseColorFactor;
        tabi::shared_ptr<Texture> m_BaseColorTexture;

        float m_MetalicFactor;
        float m_RoughnessFactor;
    };

    class Material : public IResource
    {
    public:
        static tabi::shared_ptr<Material>   LoadMaterial(const tinygltf::Model& a_Model, const std::size_t a_MaterialIndex = 0);

    public:
        bool m_DoubleSided = false;
        tabi::unique_ptr<MetalicRoughness> m_MetalicRoughness;
        tabi::shared_ptr<Texture> m_NormalTexture;

        tabi::string m_Name;
    };

    
}
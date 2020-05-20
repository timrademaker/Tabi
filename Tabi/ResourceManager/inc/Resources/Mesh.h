#pragma once

#include "../IResource.h"

#include <TabiTypes.h>
#include <TabiMath.h>

namespace tinygltf
{
    class Model;
}

namespace tabi
{
    class Mesh;
    class Material;

    class Mesh : public tabi::IResource
    {
    public:
        struct Vertex
        {
            tabi::maths::vec3 m_Pos;
            tabi::maths::vec3 m_Normal;
            tabi::maths::vec2 m_TexCoords;
        };
    public:
        static tabi::shared_ptr<Mesh> LoadMesh(const tinygltf::Model& a_Model, const std::size_t a_ModelIndex = 0);
        void Draw();

    public:
        tabi::vector<Vertex> m_Vertices;

        //tabi::vector<tabi::maths::vec3> m_VertexCoordinates;
        //tabi::vector<tabi::maths::vec3> m_VertexNormals;
        //tabi::vector<tabi::maths::vec2> m_VertexTextureCoordinates;
        tabi::vector<unsigned> m_Indices;

        graphics::MeshHandle m_MeshHandle;

        tabi::shared_ptr<Material> m_Material = nullptr;

        bool m_TextureCoordinatesAreNormalized = false;

        tabi::string m_Name;

        graphics::MeshHandle m_Handle;
    };

}
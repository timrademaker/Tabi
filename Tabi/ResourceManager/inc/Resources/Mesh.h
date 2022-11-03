#pragma once

#include "../IResource.h"

#include <TabiTypes.h>

#include <Math/vec2.h>
#include <Math/vec3.h>

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
            tabi::vec3 m_Pos;
            tabi::vec3 m_Normal;
            tabi::vec2 m_TexCoords;
        };
    public:
        Mesh() = default;
        /**
         * @params a_Path The path to the mesh to load
         */
        Mesh(const char* a_Path);

        static tabi::shared_ptr<Mesh> LoadMesh(const tinygltf::Model& a_Model, const std::size_t a_ModelIndex = 0);

        const class Buffer* GetVertexBuffer() const { return m_VertexBuffer; }
        unsigned int GetVertexCount() const { return m_VertexCount; }
        const class Buffer* GetIndexBuffer() const { return m_IndexBuffer;  }
        unsigned int GetIndexCount() const { return m_IndexCount; }

    private:
        static Mesh LoadMeshRaw(const tinygltf::Model& a_Model, const std::size_t a_ModelIndex = 0);

    public:
        tabi::vector<Vertex> m_Vertices;
        tabi::vector<unsigned> m_Indices;

        tabi::shared_ptr<Material> m_Material = nullptr;

        bool m_TextureCoordinatesAreNormalized = false;

        tabi::string m_Name;

    private:
        // TODO: Either remove these two or remove the vectors above
        unsigned int m_VertexCount = 0;
        unsigned int m_IndexCount = 0;

        class Buffer* m_VertexBuffer = nullptr;
        class Buffer* m_IndexBuffer = nullptr;
    };

}
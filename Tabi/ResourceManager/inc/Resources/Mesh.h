#pragma once

#include "../IResource.h"

#include <TabiTypes.h>

#include <Math/vec2.h>
#include <Math/vec3.h>

#include <glad/glad.h>

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
        static tabi::shared_ptr<Mesh> LoadMesh(const tinygltf::Model& a_Model, const std::size_t a_ModelIndex = 0);

    public:
        tabi::vector<Vertex> m_Vertices;
        tabi::vector<unsigned> m_Indices;

        GLuint m_VAO;
        GLuint m_VBO;
        GLuint m_EBO;

        unsigned int m_VertexCount;

        tabi::shared_ptr<Material> m_Material = nullptr;

        bool m_TextureCoordinatesAreNormalized = false;

        tabi::string m_Name;
    };

}
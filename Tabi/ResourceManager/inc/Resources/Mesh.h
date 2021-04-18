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
        Mesh() = default;
        /**
         * @params a_Path The path to the mesh to load
         * @params a_ShouldBufferMesh If true, the mesh is uploaded to the GPU after being loaded
         * @params a_CleanUpMeshDataAfterBuffering If true, removes mesh data from memory after uploading the GPU. Has no effect if a_ShouldBufferMesh is false.
         */
        Mesh(const char* a_Path, const bool a_ShouldBufferMesh = true, const bool a_CleanUpMeshDataAfterBuffering = true);

        static tabi::shared_ptr<Mesh> LoadMesh(const tinygltf::Model& a_Model, const std::size_t a_ModelIndex = 0);

    private:
        static Mesh LoadMeshRaw(const tinygltf::Model& a_Model, const std::size_t a_ModelIndex = 0);

    public:
        tabi::vector<Vertex> m_Vertices;
        tabi::vector<unsigned> m_Indices;

        GLuint m_VAO = 0;
        GLuint m_VBO = 0;
        GLuint m_EBO = 0;

        unsigned int m_VertexCount;

        tabi::shared_ptr<Material> m_Material = nullptr;

        bool m_TextureCoordinatesAreNormalized = false;

        tabi::string m_Name;
    };

}
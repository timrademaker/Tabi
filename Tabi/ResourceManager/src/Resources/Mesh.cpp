#include "Resources/Mesh.h"

#include <Resources/Material.h>

#include <TabiMath.h>
#include "ModelLoaderUtils.h"

#include <tinygltf/tiny_gltf.h>

#include <glad/glad.h>

#include <cassert>


#if defined(DIRECTX)
constexpr bool swapZPositionSign = true;
#else
constexpr bool swapZPositionSign = false;
#endif

using namespace tabi;

tabi::shared_ptr<Mesh> Mesh::LoadMesh(const tinygltf::Model& a_Model, const std::size_t a_ModelIndex)
{
    auto m = tabi::make_shared<Mesh>();

    auto& gltfMesh = a_Model.meshes[a_ModelIndex];
    m->m_Name = tabi::string(gltfMesh.name.c_str());

    for (std::size_t j = 0; j < gltfMesh.primitives.size(); ++j)
    {
        auto& attribs = gltfMesh.primitives[j].attributes;

        auto attribIter = attribs.find("NORMAL");
        if (attribIter != attribs.end())
        {
            assert(a_Model.accessors[attribIter->second].componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
            assert(a_Model.accessors[attribIter->second].type == TINYGLTF_TYPE_VEC3);

            auto& bufferView = a_Model.bufferViews[a_Model.accessors[attribIter->second].bufferView];
            auto count = a_Model.accessors[attribIter->second].count;
            //m->m_VertexNormals.reserve(count);
            m->m_Vertices.reserve(count);

            auto& buffer = a_Model.buffers[bufferView.buffer];

            auto dataStart = bufferView.byteOffset;

            for (std::size_t index = 0; index < count; ++index)
            {
                tabi::maths::vec3 vertexNormal = *(gltf::GetElementFromBuffer<tabi::maths::vec3>(&buffer.data[0], dataStart, index));

                if (swapZPositionSign)
                {
                    vertexNormal.z = -vertexNormal.z;
                }

                //m->m_VertexNormals.push_back(vertexNormal);
                if(m->m_Vertices.size() <= index)
                {
                    Mesh::Vertex v;
                    v.m_Normal = vertexNormal;
                    m->m_Vertices.push_back(v);
                }
                else
                {
                    m->m_Vertices.at(index).m_Normal = vertexNormal;
                }
            }
        }

        attribIter = attribs.find("POSITION");
        if (attribIter != attribs.end())
        {
            assert(a_Model.accessors[attribIter->second].componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
            assert(a_Model.accessors[attribIter->second].type == TINYGLTF_TYPE_VEC3);

            auto& bufferView = a_Model.bufferViews[a_Model.accessors[attribIter->second].bufferView];
            auto count = a_Model.accessors[attribIter->second].count;

            //m->m_VertexCoordinates.reserve(count);
            if(m->m_Vertices.capacity() < count)
            {
                m->m_Vertices.reserve(count);
            }

            auto& buffer = a_Model.buffers[bufferView.buffer];

            auto dataStart = bufferView.byteOffset;

            for (std::size_t index = 0; index < count; ++index)
            {
                tabi::maths::vec3 vertexPosition = *(gltf::GetElementFromBuffer<tabi::maths::vec3>(&buffer.data[0], dataStart, index));

                if (swapZPositionSign)
                {
                    vertexPosition.z = -vertexPosition.z;
                }

                //m->m_VertexCoordinates.push_back(vertexPosition);
                if (m->m_Vertices.size() <= index)
                {
                    Mesh::Vertex v;
                    v.m_Pos = vertexPosition;
                    m->m_Vertices.push_back(v);
                }
                else
                {
                    m->m_Vertices.at(index).m_Pos = vertexPosition;
                }

            }
        }

        attribIter = attribs.find("TEXCOORD_0");
        if (attribIter != attribs.end())
        {
            assert(a_Model.accessors[attribIter->second].type == TINYGLTF_TYPE_VEC2);

            auto& bufferView = a_Model.bufferViews[a_Model.accessors[attribIter->second].bufferView];
            auto count = a_Model.accessors[attribIter->second].count;

            //m->m_VertexCoordinates.reserve(count);
            if(m->m_Vertices.capacity() <= count)
            {
                m->m_Vertices.reserve(count);
            }

            auto& buffer = a_Model.buffers[bufferView.buffer];

            auto dataStart = bufferView.byteOffset;
            auto componentType = a_Model.accessors[attribIter->second].componentType;


            for (std::size_t index = 0; index < count; ++index)
            {
                tabi::maths::vec2 textureCoords;

                if (componentType == TINYGLTF_COMPONENT_TYPE_FLOAT)
                {
                    textureCoords = *(gltf::GetElementFromBuffer<tabi::maths::vec2>(&buffer.data[0], dataStart, index));
                }
                else if (componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
                {
                    auto coords = (gltf::GetElementFromBuffer<unsigned char[2]>(&buffer.data[0], dataStart, index));
                    textureCoords.x = static_cast<float>(*coords[0]);
                    textureCoords.y = static_cast<float>(*coords[1]);

                    m->m_TextureCoordinatesAreNormalized = true;
                }
                else if (componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
                {
                    auto coords = (gltf::GetElementFromBuffer<unsigned short[2]>(&buffer.data[0], dataStart, index));
                    textureCoords.x = static_cast<float>(*coords[0]);
                    textureCoords.y = static_cast<float>(*coords[1]);

                    m->m_TextureCoordinatesAreNormalized = true;
                }

                //m->m_VertexTextureCoordinates.push_back(textureCoords);
                if (m->m_Vertices.size() < index)
                {
                    Mesh::Vertex v;
                    v.m_TexCoords = textureCoords;
                    m->m_Vertices.push_back(v);
                }
                else
                {
                    m->m_Vertices.at(index).m_TexCoords = textureCoords;
                }
            }
        }

        // No need to check if the primitive has a material. If it doesn't, a default one will be used.
        m->m_Material = tabi::Material::LoadMaterial(a_Model, gltfMesh.primitives[j].material);

        // Load indices
        {
            int accessorIndex = gltfMesh.primitives[j].indices;
            assert(a_Model.accessors[accessorIndex].type == TINYGLTF_TYPE_SCALAR);

            auto& bufferView = a_Model.bufferViews[a_Model.accessors[accessorIndex].bufferView];
            auto count = a_Model.accessors[accessorIndex].count;
            m->m_Indices.reserve(count);

            auto& buffer = a_Model.buffers[bufferView.buffer];

            auto dataStart = bufferView.byteOffset;
            auto componentType = a_Model.accessors[accessorIndex].componentType;

            for (std::size_t index = 0; index < count; ++index)
            {
                unsigned int ind = 0;
                if (componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
                {
                    ind = static_cast<unsigned int>(*(gltf::GetElementFromBuffer<unsigned short>(&buffer.data[0], dataStart, index)));
                }
                else if (componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
                {
                    ind = *(gltf::GetElementFromBuffer<unsigned int>(&buffer.data[0], dataStart, index));
                }
                else if (componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
                {
                    ind = static_cast<unsigned int>(*(gltf::GetElementFromBuffer<unsigned char>(&buffer.data[0], dataStart, index)));
                }
                m->m_Indices.push_back(static_cast<unsigned>(ind));
            }
        }
    }

    return std::move(m);
}

void Mesh::Draw()
{
    // Temporary
    glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_Vertices.size()));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

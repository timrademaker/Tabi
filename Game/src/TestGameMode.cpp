#include "TestGameMode.h"

#include <IRenderer.h>

bool TestGameMode::OnInitialize()
{
    // Set shader
    auto& renderer = tabi::graphics::IRenderer::GetInstance();

    // Load mesh(es)
    auto mesh = tabi::make_shared<tabi::Mesh>();

    tabi::Mesh::Vertex v1{ {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} };
    tabi::Mesh::Vertex v2{ {0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} };
    tabi::Mesh::Vertex v3{ {0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} };
    tabi::Mesh::Vertex v4{ {-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} };
    mesh->m_Vertices.push_back(v1);
    mesh->m_Vertices.push_back(v2);
    mesh->m_Vertices.push_back(v3);
    mesh->m_Vertices.push_back(v4);

    mesh->m_Indices = { 0, 1, 3, 1, 2, 3 };
    renderer.BufferMesh(*mesh.get());

    m_Meshes.push_back(mesh);

    //mesh = Mesh::LoadMesh(gltf::LoadGLBModelFromPath("Assets/SomeFile.glb"));
    //renderer.BufferMesh(*mesh.get());
    //m_Meshes.push_back(mesh);

    return true;
}

void TestGameMode::OnRender()
{
    tabi::graphics::IRenderer& renderer = tabi::graphics::IRenderer::GetInstance();
    
    tabi::mat4 rotation = tabi::mat4::Identity();

    tabi::mat4 scale = tabi::mat4::Identity();
    tabi::mat4 translation = tabi::mat4::Identity();
    tabi::mat4 transform = tabi::mat4::CreateTransformationMatrix(translation, scale, rotation);

    for(auto& mesh : m_Meshes)
    {
        renderer.RenderMesh(*mesh, transform);
    }
}

#include "ECS/StaticMeshRenderSystem.h"
#include "ECS/StaticMeshComponent.h"

#include "Camera.h"
#include "Graphics.h"

#include <ComponentManager.h>
#include <Components/Transform.h>

#include <Math/vec4.h>
#include <Math/mat4.h>

#include <Buffer.h>
#include <GraphicsPipeline.h>
#include <IDevice.h>
#include <ICommandList.h>

#include <Resources/Material.h>

namespace tabi
{
    struct MeshConstants
    {
        mat4 modelMatrix = mat4::Identity();
        vec4 baseColorFactor{ 1.0f, 1.0f, 1.0f, 1.0f };
    };

    void UpdateAndBindRenderConstants(const Transform& a_Transform, StaticMeshComponent& a_MeshComponent, ICommandList* a_Commands)
    {
        MeshConstants constants;
        constants.modelMatrix = a_Transform.GetTransformationMatrix();
        constants.baseColorFactor = a_MeshComponent.m_Mesh->m_Material->m_MetallicRoughness->m_BaseColorFactor;

        if(a_MeshComponent.m_MeshConstants == nullptr)
        {
            BufferDescription bd;
            bd.m_Role = EBufferRole::Constant;
            bd.m_SizeInBytes = sizeof(MeshConstants);
            bd.m_Stride = sizeof(MeshConstants);
            bd.m_Format = EFormat::RGBA32_float;

            char bufferName[64];
            snprintf(bufferName, sizeof(bufferName), "%s Constants", a_MeshComponent.m_Mesh->m_Name.c_str());
            a_MeshComponent.m_MeshConstants = IDevice::GetInstance()->CreateBuffer(bd, bufferName);
        }

        a_Commands->CopyDataToBuffer(a_MeshComponent.m_MeshConstants, &constants, sizeof(MeshConstants));
        a_Commands->BindConstantBuffer(a_MeshComponent.m_MeshConstants, 1);
    }
}

tabi::StaticMeshRenderSystem::StaticMeshRenderSystem(tabi::ComponentManager* a_ComponentManager)
    : ISystem(a_ComponentManager)
{
    RequireComponent<Transform>();
    RequireComponent<StaticMeshComponent>();
}

tabi::StaticMeshRenderSystem::~StaticMeshRenderSystem()
{
    auto* device = IDevice::GetInstance();
    // Slightly hacky, but this system is the only one with these pointers
    auto* vertexShader = const_cast<Shader*>(m_MeshInstancePipeline->GetPipelineDescription().m_VertexShader);
    device->DestroyShader(vertexShader);
    auto* pixelShader = const_cast<Shader*>(m_MeshInstancePipeline->GetPipelineDescription().m_PixelShader);
    device->DestroyShader(pixelShader);

    device->DestroyGraphicsPipeline(m_MeshInstancePipeline);
    device->DestroyBuffer(m_ConstantDataBuffer);
}

void tabi::StaticMeshRenderSystem::OnRender()
{
    if (m_MeshInstancePipeline == nullptr)
    {
        Setup();
    }

    auto* device = IDevice::GetInstance();
    auto* commands = device->CreateCommandList("MeshInstance Rendering");
    commands->BeginRecording();

    commands->SetRenderTarget(nullptr);
    commands->UseGraphicsPipeline(m_MeshInstancePipeline);

    {
        auto* camera = graphics::GetMainCamera();
        const mat4 eye = camera->GetView();
        const mat4 projection = camera->GetProjection();
        const mat4 res = eye * projection;

        commands->CopyDataToBuffer(m_ConstantDataBuffer, res.v, sizeof(res));
        commands->BindConstantBuffer(m_ConstantDataBuffer, 0);
    }

    // TODO: Instead of this, gather all meshes/transforms and sort them by mesh?
    for (auto& ent : m_Entities)
    {
        auto& meshComponent = m_ComponentManager->GetComponent<StaticMeshComponent>(ent);
        if(!meshComponent.m_IsVisible)
        {
            continue;
        }

        const auto& mesh = meshComponent.m_Mesh;
        const auto& transform = m_ComponentManager->GetComponent<Transform>(ent);

        UpdateAndBindRenderConstants(transform, meshComponent, commands);

        const Buffer* vertexBuffers[] = { mesh->GetVertexBuffer() };
        commands->BindVertexBuffers(0, vertexBuffers, 1);
        commands->BindIndexBuffer(mesh->GetIndexBuffer());
        commands->BindTexture(mesh->m_Material->m_MetallicRoughness->m_BaseColorTexture->GetTexture(), 0);

        commands->DrawIndexed(mesh->GetIndexCount());
    }

    commands->EndRecording();
    device->ExecuteCommandList(commands);
    device->DestroyCommandList(commands);
}

void tabi::StaticMeshRenderSystem::Setup()
{
    GraphicsPipelineDescription gpd;
    gpd.m_VertexShader = LoadShader("TabiAssets/Shaders/VertexShader.vert", EShaderType::Vertex, "Mesh Vert Shader");
    gpd.m_PixelShader = LoadShader("TabiAssets/Shaders/SingleTextureShader.frag", EShaderType::Pixel, "Mesh Frag Shader");
    gpd.m_Topology = EToplolgy::Triangle;

    gpd.m_VertexInputLayout.m_InputElements[0] = VertexInputElement{ 0, 0, "POSITION", EFormat::RGB32_float, EInstanceDataStepClassification::PerVertex, 0 };
    gpd.m_VertexInputLayout.m_InputElements[1] = VertexInputElement{ 0, 0, "NORMAL", EFormat::RGB32_float, EInstanceDataStepClassification::PerVertex, 0 };
    gpd.m_VertexInputLayout.m_InputElements[2] = VertexInputElement{ 0, 0, "TEXCOORD", EFormat::RG32_float, EInstanceDataStepClassification::PerVertex, 0 };
    gpd.m_VertexInputLayout.m_NumInputElements = 3;

    gpd.m_RasterizerState.m_TriangleFrontIsCounterClockwise = true;

    auto* device = IDevice::GetInstance();
    m_MeshInstancePipeline = device->CreateGraphicsPipeline(gpd, "Static Mesh Pipeline");

    m_ConstantDataBuffer = device->CreateBuffer({ EFormat::RGBA32_float, EBufferRole::Constant, sizeof(mat4), 0 });
}

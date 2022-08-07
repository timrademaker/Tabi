#include "TestGameMode.h"

#include <TabiTypes.h>

#include <TabiLogger.h>

#include <Graphics.h>

#include <IDevice.h>
#include <ICommandList.h>

#include <Buffer.h>
#include <GraphicsPipeline.h>
#include <RenderTarget.h>
#include <Texture.h>
#include <Enums/GraphicsPipelineEnums.h>

#include <Resources/Mesh.h>
#include <Resources/Model.h>

#include "TextureUpdateDescription.h"
#include "Resources/Material.h"

bool TestGameMode::OnInitialize()
{
    tabi::InputManager::SetCursorCapture(true);
    tabi::InputManager::SetCursorVisible(false);

    m_Camera = tabi::make_shared<MovableCamera>(16.0f / 9.0f);
    m_Camera->MoveBy(tabi::vec3(0, 0, 5));
    m_Camera->SetNear(1.0f);
    m_Camera->SetFar(1000.0f);

    auto* device = tabi::IDevice::GetInstance();
    m_CommandList = device->CreateCommandList();
    m_CommandList->BeginRecording();

    // GLB model test
    {
        const auto model = tabi::Model::LoadBinaryModelFromPath("Assets/Duck.glb");
        const auto mesh = model->m_Meshes[0];

        Model m;

        m.m_Scale /= 15.0f;
        m.m_Position = tabi::vec3{ -10.0f, -5.0f, -15.0f };
        m.m_Rotation = tabi::vec3{ 0.0f, -1.57f, 0.0f };

        m.m_VertexBuffer = device->CreateBuffer({ tabi::EFormat::RGB32_float, tabi::EBufferRole::Vertex, sizeof(tabi::Mesh::Vertex) * mesh->m_VertexCount, sizeof(tabi::Mesh::Vertex) });
        m.m_VertexCount = mesh->m_VertexCount;
        m_CommandList->CopyDataToBuffer(m.m_VertexBuffer, reinterpret_cast<const char*>(mesh->m_Vertices.data()), sizeof(tabi::Mesh::Vertex) * mesh->m_VertexCount, 0);

        m.m_IndexBuffer = device->CreateBuffer({ tabi::EFormat::R32_uint, tabi::EBufferRole::Index, sizeof(mesh->m_Indices[0]) * mesh->m_Indices.size(), 0 });
        m.m_IndexCount = mesh->m_Indices.size();
        m_CommandList->CopyDataToBuffer(m.m_IndexBuffer, reinterpret_cast<const char*>(&mesh->m_Indices[0]), sizeof(mesh->m_Indices[0]) * mesh->m_Indices.size(), 0);

        auto tex = mesh->m_Material->m_MetalicRoughness->m_BaseColorTexture;
        if (tex)
        {
            tabi::TextureDescription td{ tabi::ETextureDimension::Tex2D, tabi::ETextureRole::Texture, tex->m_Format };

            td.m_Width = tex->m_Width;
            td.m_Height = tex->m_Height;

            m.m_ColorTexture = device->CreateTexture(td, "GLB texture");

            tabi::TextureUpdateDescription tud;
            tud.m_Data = reinterpret_cast<const char*>(tex->m_TextureData.data());
            tud.m_DataWidth = tex->m_Width;
            tud.m_DataHeight = tex->m_Height;

            m_CommandList->CopyDataToTexture(m.m_ColorTexture, tud);
        }

        m_Models.emplace_back(m);
    }

    m_ModelData = device->CreateBuffer({ tabi::EFormat::RGBA32_float, tabi::EBufferRole::Constant, sizeof(ModelData), 0 });

    // Model rendering test
    {
        Model m;

        const float vertices[] = {
            // X, Y, Z,             Normal,                 U, V
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
            0.0f,  0.5f, 0.0f,      0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
        };
        m.m_VertexBuffer = device->CreateBuffer({ tabi::EFormat::RGB32_float, tabi::EBufferRole::Vertex, sizeof(vertices), sizeof(vertices) / 4 });
        m.m_VertexCount = std::size(vertices) / 6;
        m_CommandList->CopyDataToBuffer(m.m_VertexBuffer, reinterpret_cast<const char*>(&vertices[0]), sizeof(vertices), 0);

        const uint32_t indices[] = {
            0, 1, 3, 1, 2, 3
        };
        m.m_IndexBuffer = device->CreateBuffer({ tabi::EFormat::R32_uint, tabi::EBufferRole::Index, sizeof(indices), 0 });
        m.m_IndexCount = std::size(indices);
        m_CommandList->CopyDataToBuffer(m.m_IndexBuffer, reinterpret_cast<const char*>(&indices[0]), sizeof(indices), 0);

        m_Models.emplace_back(m);

        m_ConstBuffer = device->CreateBuffer({ tabi::EFormat::RGBA32_float, tabi::EBufferRole::Constant, sizeof(tabi::mat4), 0 });

        // Create vertex pipeline
        const auto* vertShader = tabi::graphics::LoadShader("TabiAssets/Shaders/VertexShader.vert", tabi::EShaderType::Vertex, "Test vertex shader");
        const auto* pixShader = tabi::graphics::LoadShader("TabiAssets/Shaders/SingleTextureShader.frag", tabi::EShaderType::Pixel, "Test pixel shader");

        tabi::VertexInputLayout vertexInput;
        vertexInput.m_NumInputElements = 3;

        const tabi::VertexInputElement posElement{ 0, 0, "POSITION", tabi::EFormat::RGB32_float, tabi::EInstanceDataStepClassification::PerVertex, 0 };
        const tabi::VertexInputElement normalElement{ 0, 0, "NORMAL", tabi::EFormat::RGB32_float, tabi::EInstanceDataStepClassification::PerVertex, 0 };
        const tabi::VertexInputElement texCoordElement{ 0, 0, "TEXCOORD", tabi::EFormat::RG32_float, tabi::EInstanceDataStepClassification::PerVertex, 0 };
        vertexInput.m_InputElements[0] = posElement;
        vertexInput.m_InputElements[1] = normalElement;
        vertexInput.m_InputElements[2] = texCoordElement;

        tabi::BlendState blendState;
        blendState.m_BlendEnabled = false;
        tabi::RasterizerState rasterizerState;
        rasterizerState.m_TriangleFrontIsCounterClockwise = true;
        rasterizerState.m_CullMode = tabi::ECullMode::Back;
        tabi::DepthStencilState depthStencilState;
        depthStencilState.m_EnableDepthTest = true;

        const auto pipelineDesc = tabi::GraphicsPipelineDescription{ vertShader, pixShader, tabi::EToplolgy::Triangle, false, {blendState}, rasterizerState, depthStencilState, vertexInput };
        m_MeshPipeline = device->CreateGraphicsPipeline(pipelineDesc, "Test pipeline");
    }

    // Render target test
    {
        const float quadVertices[] = {
            // X, Y,             U, V
            -0.8f, -0.8f,       0.0f, 0.0f,
            0.8f, -0.8f,        1.0f, 0.0f,
            0.8f, 0.8f,         1.0f, 1.0f,
            -0.8f, 0.8f,        0.0f, 1.0f
        };
        m_UIQuad.m_VertexBuffer = device->CreateBuffer({ tabi::EFormat::RG32_float, tabi::EBufferRole::Vertex, sizeof(quadVertices), sizeof(quadVertices) / 4 });
        m_UIQuad.m_VertexCount = sizeof(quadVertices) / sizeof(float) / 4;
        m_CommandList->CopyDataToBuffer(m_UIQuad.m_VertexBuffer, reinterpret_cast<const char*>(&quadVertices[0]), sizeof(quadVertices), 0);

        const uint32_t quadIndices[] = {
        0, 1, 2, 0, 2, 3
        };
        m_UIQuad.m_IndexBuffer = device->CreateBuffer({ tabi::EFormat::R32_uint, tabi::EBufferRole::Index, sizeof(quadIndices), 0 });
        m_UIQuad.m_IndexCount = std::size(quadIndices);
        m_CommandList->CopyDataToBuffer(m_UIQuad.m_IndexBuffer, reinterpret_cast<const char*>(&quadIndices[0]), sizeof(quadIndices), 0);

        // Create vertex pipeline
        const auto* uiVertShader = tabi::graphics::LoadShader("TabiAssets/Shaders/UI.vert", tabi::EShaderType::Vertex, "UI vertex shader");
        const auto* uiPixShader = tabi::graphics::LoadShader("TabiAssets/Shaders/UI.frag", tabi::EShaderType::Pixel, "UI pixel shader");

        tabi::VertexInputLayout uiVertexInput;
        uiVertexInput.m_NumInputElements = 2;

        uiVertexInput.m_InputElements[0] = { 0, 0, "POSITION", tabi::EFormat::RG32_float, tabi::EInstanceDataStepClassification::PerVertex, 0 };
        uiVertexInput.m_InputElements[1] = { 0, 0, "TEXCOORD", tabi::EFormat::RG32_float, tabi::EInstanceDataStepClassification::PerVertex, 0 };

        tabi::BlendState blendState;
        blendState.m_BlendEnabled = false;
        tabi::RasterizerState rasterizerState;
        rasterizerState.m_TriangleFrontIsCounterClockwise = true;
        rasterizerState.m_CullMode = tabi::ECullMode::Back;
        tabi::DepthStencilState depthStencilState;
        depthStencilState.m_EnableDepthTest = false;

        m_UIPipeline = device->CreateGraphicsPipeline(tabi::GraphicsPipelineDescription{ uiVertShader, uiPixShader, tabi::EToplolgy::Triangle, false, {blendState}, rasterizerState, depthStencilState, uiVertexInput }, "UI pipeline");

        m_DrawTex = device->CreateTexture(tabi::TextureDescription{ tabi::ETextureDimension::Tex2D, tabi::ETextureRole::RenderTexture, tabi::EFormat::RGBA32_uint, 1280, 720, 1, 1 });
        m_DepthTex = device->CreateTexture(tabi::TextureDescription{ tabi::ETextureDimension::Tex2D, tabi::ETextureRole::DepthStencil, tabi::EFormat::Depth24Stencil8, 1280, 720, 1, 1 });

        tabi::RenderTargetDescription rtd;
        rtd.m_RenderTextures[0] = { m_DrawTex };
        rtd.m_DepthStencil = { m_DepthTex };
        m_RenderTarget = device->CreateRenderTarget(rtd);
    }

    m_CommandList->EndRecording();

    return true;
}

void TestGameMode::OnUpdate(float a_DeltaTime)
{
    m_Camera->Update(a_DeltaTime);
}

void TestGameMode::OnRender()
{
    m_CommandList->BeginRecording();

    
    static constexpr float mainClearCol[] = { 0.25f, 0.3f, 1.0f, 1.0f };
    m_CommandList->ClearRenderTarget(nullptr, mainClearCol);
    m_CommandList->ClearDepthStencil(nullptr);

    static constexpr float renderTargetClearCol[] = { 0.6f, 0.1f, 0.5f, 1.0f };
    m_CommandList->ClearRenderTarget(m_RenderTarget, renderTargetClearCol);
    m_CommandList->ClearDepthStencil(m_RenderTarget);

    m_CommandList->SetRenderTarget(m_RenderTarget);

    const tabi::mat4 eye = m_Camera->GetView();
    const tabi::mat4 projection = m_Camera->GetProjection();
    const tabi::mat4 res = eye * projection;

    m_CommandList->CopyDataToBuffer(m_ConstBuffer, reinterpret_cast<const char*>(res.v), sizeof(res), 0);
    m_CommandList->BindConstantBuffer(m_ConstBuffer, 0);
    m_CommandList->UseGraphicsPipeline(m_MeshPipeline);

    m_CommandList->BindConstantBuffer(m_ModelData, 1);

    for(size_t i = 0; i < m_Models.size(); ++i)
    {
        m_CommandList->BindVertexBuffers(0, &m_Models[i].m_VertexBuffer, 1);
        m_CommandList->BindIndexBuffer(m_Models[i].m_IndexBuffer);
        m_CommandList->BindTexture(m_Models[i].m_ColorTexture, 0);

        ModelData md;
        auto pos = tabi::mat4::Identity();
        pos.Translate(m_Models[i].m_Position);
        auto rot = tabi::mat4::Identity();
        rot.SetRotation(m_Models[i].m_Rotation);
        auto scale = tabi::mat4::Identity();
        scale.SetScale(m_Models[i].m_Scale);
        md.m_ModelMatrix = tabi::mat4::CreateTransformationMatrix(pos, scale, rot);
        m_CommandList->CopyDataToBuffer(m_ModelData, reinterpret_cast<const char*>(&md), sizeof(md), 0);

        m_CommandList->DrawIndexed(m_Models[i].m_IndexCount);
    }

    m_CommandList->SetRenderTarget(nullptr);
    m_CommandList->BindTexture(m_DrawTex, 0);
    m_CommandList->UseGraphicsPipeline(m_UIPipeline);
    m_CommandList->BindVertexBuffers(0, &m_UIQuad.m_VertexBuffer, 1);
    m_CommandList->BindIndexBuffer(m_UIQuad.m_IndexBuffer);
    m_CommandList->DrawIndexed(m_UIQuad.m_IndexCount);

    m_CommandList->EndRecording();

    tabi::IDevice::GetInstance()->ExecuteCommandList(m_CommandList);
    m_CommandList->Reset();
}

void TestGameMode::OnDestroy()
{
    auto* device = tabi::IDevice::GetInstance();

    for (size_t i = 0; i < m_Models.size(); ++i)
    {
        device->DestroyBuffer(m_Models[i].m_VertexBuffer);
        device->DestroyBuffer(m_Models[i].m_IndexBuffer);
    }
    m_Models.clear();

    device->DestroyBuffer(m_ConstBuffer);
    device->DestroyGraphicsPipeline(m_MeshPipeline);
    device->DestroyCommandList(m_CommandList);

    device->DestroyGraphicsPipeline(m_UIPipeline);
    device->DestroyBuffer(m_UIQuad.m_VertexBuffer);
    device->DestroyBuffer(m_UIQuad.m_IndexBuffer);
    device->DestroyTexture(m_DrawTex);
    device->DestroyTexture(m_DepthTex);
}

#include "TestGameMode.h"

#include <TabiTypes.h>

#include <TabiLogger.h>

#include <Graphics.h>

#include <IDevice.h>
#include <ICommandList.h>

#include <Buffer.h>
#include <GraphicsPipeline.h>
#include <Enums/GraphicsPipelineEnums.h>

bool TestGameMode::OnInitialize()
{
    tabi::InputManager::SetCursorCapture(true);
    tabi::InputManager::SetCursorVisible(false);

    m_Camera = tabi::make_shared<MovableCamera>(16.0f / 9.0f);
    m_Camera->m_Camera->MoveBy(tabi::vec3(0, 0, 5));

    auto* device = tabi::IDevice::GetInstance();
    m_CommandList = device->CreateCommandList();
    m_CommandList->BeginRecording();

    const float vertices[] = {
        // X, Y, Z,             R, G, B
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,      0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 1.0f
    };
    auto* vertexBuffer = device->CreateBuffer({ tabi::EFormat::RGB32_float, tabi::EBufferRole::Vertex, sizeof(vertices), sizeof(vertices) / 4 });
    m_VertexBuffers.push_back(vertexBuffer);
    m_CommandList->CopyDataToBuffer(vertexBuffer, reinterpret_cast<const char*>(&vertices[0]), sizeof(vertices), 0);

    const uint32_t indices[] = {
        0, 1, 3, 1, 2, 3
    };
    auto* indexBuffer = device->CreateBuffer({ tabi::EFormat::R32_uint, tabi::EBufferRole::Index, sizeof(indices), 0 });
    m_CommandList->CopyDataToBuffer(indexBuffer, reinterpret_cast<const char*>(&indices[0]), sizeof(indices), 0);
    m_IndexBuffers.push_back(indexBuffer);
    
    m_ConstBuffer = device->CreateBuffer({ tabi::EFormat::RGBA32_float, tabi::EBufferRole::Constant, sizeof(tabi::mat4), 0 });

    // Create vertex pipeline
    const auto* vertShader = tabi::graphics::LoadShader("TabiAssets/Shaders/VertexShader.vert", tabi::EShaderType::Vertex, "Test vertex shader");
    const auto* pixShader = tabi::graphics::LoadShader("TabiAssets/Shaders/FragmentShader.frag", tabi::EShaderType::Pixel, "Test pixel shader");

    tabi::VertexInputLayout vertexInput;
    vertexInput.m_NumInputElements = 2;

    const tabi::VertexInputElement posElement{ 0, 0, "POSITION", tabi::EFormat::RGB32_float, tabi::EInstanceDataStepClassification::PerVertex, 0 };
    const tabi::VertexInputElement colElement{ 0, 0, "COLOR", tabi::EFormat::RGB32_float, tabi::EInstanceDataStepClassification::PerVertex, 0 };
    vertexInput.m_InputElements[0] = posElement;
    vertexInput.m_InputElements[1] = colElement;

    tabi::BlendState blendState;
    blendState.m_BlendEnabled = false;
    tabi::RasterizerState rasterizerState;
    rasterizerState.m_TriangleFrontIsCounterClockwise = true;
    rasterizerState.m_CullMode = tabi::ECullMode::None;
    tabi::DepthStencilState depthStencilState;
    depthStencilState.m_EnableDepthTest = false;

    const auto pipelineDesc = tabi::GraphicsPipelineDescription{ vertShader, pixShader, tabi::EToplolgy::Triangle, blendState, rasterizerState, depthStencilState, vertexInput };
    m_MeshPipeline = device->CreateGraphicsPipeline(pipelineDesc, "Test pipeline");

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

    static constexpr float clearCol[] = { 0.25f, 0.3f, 1.0f, 1.0f };
    m_CommandList->ClearRenderTarget(nullptr, clearCol);

    const tabi::mat4 eye = m_Camera->m_Camera->GetView();
    const tabi::mat4 projection = m_Camera->m_Camera->GetProjection();
    const tabi::mat4 res = eye * projection;

    m_CommandList->CopyDataToBuffer(m_ConstBuffer, reinterpret_cast<const char*>(res.v), sizeof(res), 0);
    m_CommandList->BindConstantBuffer(m_ConstBuffer, 0);
    m_CommandList->UseGraphicsPipeline(m_MeshPipeline);

    TABI_ASSERT(m_VertexBuffers.size() == m_IndexBuffers.size());
    for(size_t i = 0; i < m_VertexBuffers.size(); ++i)
    {
        m_CommandList->BindVertexBuffers(0, &m_VertexBuffers[i], 1);
        m_CommandList->BindIndexBuffer(m_IndexBuffers[i]);
        m_CommandList->DrawIndexed(6);
    }

    m_CommandList->EndRecording();

    tabi::IDevice::GetInstance()->ExecuteCommandList(m_CommandList);
    m_CommandList->Reset();
}

void TestGameMode::OnDestroy()
{
    auto* device = tabi::IDevice::GetInstance();

    for (size_t i = 0; i < m_VertexBuffers.size(); ++i)
    {
        device->DestroyBuffer(m_VertexBuffers[i]);
        device->DestroyBuffer(m_IndexBuffers[i]);
    }
    m_VertexBuffers.clear();
    m_IndexBuffers.clear();

    device->DestroyBuffer(m_ConstBuffer);
    device->DestroyGraphicsPipeline(m_MeshPipeline);
    device->DestroyCommandList(m_CommandList);
}

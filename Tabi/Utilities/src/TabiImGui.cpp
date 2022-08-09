#include "TabiImGui.h"

#include <Math/mat4.h>

#include <IDevice.h>
#include <ICommandList.h>
#include <Texture.h>
#include <TextureUpdateDescription.h>
#include <GraphicsPipeline.h>
#include <Sampler.h>
#include <Buffer.h>

#include <Graphics.h>

#include <InputManager.h>

#include <imgui/imgui.h>

#include <glad/gl.h>


#include <IWindow.h>

namespace tabi
{
    namespace imgui
    {
        struct ImplementationData
        {
            ICommandList* m_CommandList = nullptr;
            GraphicsPipeline* m_GraphicsPipeline = nullptr;
            Sampler* m_Sampler = nullptr;
            Texture* m_FontTexture = nullptr;

            Buffer* m_VertexBuffer = nullptr;
            Buffer* m_IndexBuffer = nullptr;
            Buffer* m_ConstantBuffer = nullptr;

            size_t m_VertexBufferSize = 0;
            size_t m_IndexBufferSize = 0;

            Shader* m_VertexShader = nullptr;
            Shader* m_PixelShader = nullptr;
        };

        struct ImGuiConstantBufferData
        {
            tabi::mat4 m_OrthoMatrix;
        };
    }
}

tabi::imgui::ImplementationData* GetImplementationData()
{
    return ImGui::GetCurrentContext() ? static_cast<tabi::imgui::ImplementationData*>(ImGui::GetIO().BackendRendererUserData) : nullptr;
}

void tabi::imgui::Init()
{
    // TODO: Set up window resize event here (io.DisplaySize.x/y)

    ImplementationData* impData = new ImplementationData;

    auto* device = IDevice::GetInstance();

    impData->m_CommandList = device->CreateCommandList("ImGui Commands");
    impData->m_CommandList->BeginRecording();

    ::ImGui::CreateContext();
    auto& io = ::ImGui::GetIO();
    io.BackendRendererUserData = (void*)impData;
    io.BackendRendererName = "imgui_impl_tabi";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    // TODO: Set up io

    int width;
    int height;
    unsigned char* pixels = nullptr;
    // TODO: Can we use the alpha-only function?
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    impData->m_FontTexture = device->CreateTexture(tabi::TextureDescription{ ETextureDimension::Tex2D, ETextureRole::Texture, EFormat::RGBA8_unorm, static_cast<uint64_t>(width), static_cast<uint64_t>(height), 1, 1 }, "ImGui Font");
    TextureUpdateDescription tud;
    tud.m_Data = pixels;
    tud.m_DataWidth = width;
    tud.m_DataHeight = height;

    impData->m_CommandList->CopyDataToTexture(impData->m_FontTexture, tud);
    io.Fonts->SetTexID(impData->m_FontTexture);

    impData->m_VertexShader = tabi::graphics::LoadShader("TabiAssets/Shaders/imgui.vert", EShaderType::Vertex, "ImGui vertex shader");
    impData->m_PixelShader = tabi::graphics::LoadShader("TabiAssets/Shaders/imgui.frag", EShaderType::Pixel, "ImGui pixel shader");
    
    GraphicsPipelineDescription gpd;
    gpd.m_VertexShader = impData->m_VertexShader;
    gpd.m_PixelShader = impData->m_PixelShader;
    gpd.m_Topology = EToplolgy::Triangle;

    gpd.m_IndividualBlend = false;
    gpd.m_BlendState[0].m_BlendEnabled = true;
    gpd.m_BlendState[0].m_SourceBlendFactorRGB = EBlendFactor::SrcAlpha;
    gpd.m_BlendState[0].m_DestBlendFactorRGB = EBlendFactor::InvDstAlpha;
    gpd.m_BlendState[0].m_SourceBlendFactorAlpha = EBlendFactor::One;
    gpd.m_BlendState[0].m_DestBlendFactorAlpha = EBlendFactor::InvSrcAlpha;

    gpd.m_RasterizerState.m_CullMode = ECullMode::None;
    gpd.m_DepthStencilState.m_FrontStencilState.m_StencilFunc = EComparisonFunction::Never;
    gpd.m_DepthStencilState.m_BackStencilState.m_StencilFunc = EComparisonFunction::Never;
    gpd.m_DepthStencilState.m_EnableDepthTest = false;

    // TODO: Setup render state: scissor enabled
    // TODO: Setup viewport covering draw_data->DisplayPos to draw_data->DisplayPos + draw_data->DisplaySize
    // TODO: Setup orthographic projection matrix cover draw_data->DisplayPos to draw_data->DisplayPos + draw_data->DisplaySize

    gpd.m_VertexInputLayout.m_NumInputElements = 3;
    gpd.m_VertexInputLayout.m_InputElements[0] = VertexInputElement{ 0, 0, "POSITION", EFormat::RG32_float, EInstanceDataStepClassification::PerVertex, 0 };
    gpd.m_VertexInputLayout.m_InputElements[1] = VertexInputElement{ 0, 0, "TEXCOORD", EFormat::RG32_float, EInstanceDataStepClassification::PerVertex, 0 };
    gpd.m_VertexInputLayout.m_InputElements[2] = VertexInputElement{ 0, 0, "COLOR", EFormat::RGBA8_unorm, EInstanceDataStepClassification::PerVertex, 0 };

    impData->m_GraphicsPipeline = device->CreateGraphicsPipeline(gpd, "ImGui pipeline");

    // TODO: Verify these settings
    impData->m_Sampler = device->CreateSampler({ EFilterMode::Linear, EFilterMode::Linear, tabi::EMipMapMode::Linear, tabi::EWrapMode::Clamp });
    // TODO: Size is placeholder, as we can create a new buffer while drawing if needed.
    impData->m_VertexBuffer = device->CreateBuffer({ EFormat::RG32_float, EBufferRole::Vertex, 2048 * sizeof(ImDrawVert), sizeof(ImDrawVert) }, "ImGui vertices");
    impData->m_VertexBufferSize = 2048 * sizeof(ImDrawVert);
    impData->m_IndexBuffer = device->CreateBuffer({ sizeof(ImDrawIdx) == 2 ? EFormat::R16_uint : EFormat::R32_uint, EBufferRole::Index, 2048 * sizeof(ImDrawIdx), sizeof(ImDrawIdx) }, "ImGui indices");
    impData->m_IndexBufferSize = 2048 * sizeof(ImDrawIdx);

    impData->m_ConstantBuffer = device->CreateBuffer({ EFormat::RGBA32_float, EBufferRole::Constant, sizeof(ImGuiConstantBufferData), 0 }, "ImGui cbuffer");

    impData->m_CommandList->EndRecording();
    device->ExecuteCommandList(impData->m_CommandList);
}

void tabi::imgui::NewFrame(float a_DeltaTime)
{
    const auto& window = tabi::graphics::IWindow::GetInstance();
    uint32_t ww;
    uint32_t wh;
    window.GetWindowDimensions(ww, wh);

    // TODO: Update button state
    auto& io = ::ImGui::GetIO();
    io.DeltaTime = a_DeltaTime;
    io.DisplaySize.x = ww;
    io.DisplaySize.y = wh;
    // TODO:
    // io.AddMousePosEvent();
    //io.AddMouseButtonEvent(0, );
    //io.AddMouseButtonEvent(1, );
    //io.AddMouseWheelEvent();

    ::ImGui::NewFrame();
}

namespace tabi
{
    namespace imgui
    {
        void SetUpRenderState(const ImDrawData* a_DrawData, int32_t a_FrameBufferWidth, int32_t a_FrameBufferheight)
        {
            auto* data = GetImplementationData();
            TABI_ASSERT(data);

            // TODO: glViewport(0, 0, (GLsizei)a_FrameBufferWidth, (GLsizei)a_FrameBufferheight);
            const float L = a_DrawData->DisplayPos.x;
            const float R = a_DrawData->DisplayPos.x + a_DrawData->DisplaySize.x;
            const float T = a_DrawData->DisplayPos.y;
            const float B = a_DrawData->DisplayPos.y + a_DrawData->DisplaySize.y;

            // TODO: This can probably be done more efficiently, as there are only 4 values that need to be passed to the shader.
            ImGuiConstantBufferData bufferData;
            bufferData.m_OrthoMatrix = tabi::mat4(
                2.0f / (R - L), 0.0f, 0.0f, 0.0f,
                0.0f, 2.0f / (T - B), 0.0f, 0.0f,
                0.0f, 0.0f, -1.0f, 0.0f,
                (R + L) / (L - R), (T + B) / (B - T), 0.0f, 1.0f
            );

            data->m_CommandList->CopyDataToBuffer(data->m_ConstantBuffer, reinterpret_cast<const char*>(&bufferData), sizeof(ImGuiConstantBufferData));

            data->m_CommandList->UseGraphicsPipeline(data->m_GraphicsPipeline);

            // TODO: Should we do this?
            /*
            #ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_BIND_SAMPLER
            if (bd->GlVersion >= 330)
                glBindSampler(0, 0); // We use combined texture/sampler state. Applications using GL 3.3 may set that otherwise.
            #endif
            */
            data->m_CommandList->BindSampler(data->m_Sampler, 0);

            data->m_CommandList->BindVertexBuffers(0, &data->m_VertexBuffer, 1);
            data->m_CommandList->BindIndexBuffer(data->m_IndexBuffer);
            data->m_CommandList->BindConstantBuffer(data->m_ConstantBuffer, 0);
        }
    }
}

void tabi::imgui::EndFrame()
{
    ::ImGui::EndFrame();
    ::ImGui::Render();

    ImDrawData* drawData = ::ImGui::GetDrawData();
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    const int32_t fbWidth = static_cast<int>(drawData->DisplaySize.x * drawData->FramebufferScale.x);
    const int32_t fbHeight = static_cast<int>(drawData->DisplaySize.y * drawData->FramebufferScale.y);
    if (fbWidth <= 0 || fbHeight <= 0)
        return;

    auto* data = GetImplementationData();
    TABI_ASSERT(data);

    data->m_CommandList->BeginRecording();

    /*
    // Will project scissor/clipping rectangles into framebuffer space
    ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
    ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)
    */
    
    SetUpRenderState(drawData, fbWidth, fbHeight);

    for (size_t i = 0; i < drawData->CmdListsCount; ++i)
    {
        const ImDrawList* drawList = drawData->CmdLists[i];

        const GLsizeiptr vertexBufferDataSize = static_cast<GLsizeiptr>(drawList->VtxBuffer.Size) * static_cast<int>(sizeof(ImDrawVert));
        const GLsizeiptr indexBufferDataSize = static_cast<GLsizeiptr>(drawList->IdxBuffer.Size) * static_cast<int>(sizeof(ImDrawIdx));
        if (data->m_VertexBufferSize < vertexBufferDataSize)
        {
            data->m_VertexBufferSize = vertexBufferDataSize;
            // TODO: Create new buffer
        }
        if (data->m_IndexBufferSize < indexBufferDataSize)
        {
            data->m_IndexBufferSize = indexBufferDataSize;
            // TODO: Create new buffer
        }
        data->m_CommandList->CopyDataToBuffer(data->m_VertexBuffer, reinterpret_cast<const char*>(drawList->VtxBuffer.Data), vertexBufferDataSize, 0);
        data->m_CommandList->CopyDataToBuffer(data->m_IndexBuffer, reinterpret_cast<const char*>(drawList->IdxBuffer.Data), indexBufferDataSize, 0);

        for (size_t j = 0; j < drawList->CmdBuffer.Size; ++j)
        {
            const ImDrawCmd* cmd = &drawList->CmdBuffer[j];
            if (cmd->UserCallback != nullptr)
            {
                if (cmd->UserCallback == ImDrawCallback_ResetRenderState)
                {
                    SetUpRenderState(drawData, fbWidth, fbHeight);
                }
                else
                {
                    cmd->UserCallback(drawList, cmd);
                }
            }
            else
            {
                /* TODO:
                // Project scissor/clipping rectangles into framebuffer space
                ImVec2 clip_min((pcmd->ClipRect.x - clip_off.x) * clip_scale.x, (pcmd->ClipRect.y - clip_off.y) * clip_scale.y);
                ImVec2 clip_max((pcmd->ClipRect.z - clip_off.x) * clip_scale.x, (pcmd->ClipRect.w - clip_off.y) * clip_scale.y);
                if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
                    continue;

                // Apply scissor/clipping rectangle (Y is inverted in OpenGL)
                glScissor((int)clip_min.x, (int)((float)fb_height - clip_max.y), (int)(clip_max.x - clip_min.x), (int)(clip_max.y - clip_min.y));
                */

                data->m_CommandList->BindTexture(static_cast<Texture*>(cmd->GetTexID()), 0);
                data->m_CommandList->DrawIndexed(cmd->ElemCount, cmd->IdxOffset, cmd->VtxOffset);
            }
        }
    }

    data->m_CommandList->EndRecording();
    IDevice::GetInstance()->ExecuteCommandList(data->m_CommandList);
    data->m_CommandList->Reset();
}

void tabi::imgui::Shutdown()
{
    auto* data = GetImplementationData();
    if (data)
    {
        auto* device = IDevice::GetInstance();
        device->DestroyCommandList(data->m_CommandList);
        device->DestroyGraphicsPipeline(data->m_GraphicsPipeline);
        device->DestroySampler(data->m_Sampler);
        device->DestroyBuffer(data->m_VertexBuffer);
        device->DestroyBuffer(data->m_IndexBuffer);
        device->DestroyBuffer(data->m_ConstantBuffer);
        device->DestroyShader(data->m_VertexShader);
        device->DestroyShader(data->m_PixelShader);
        device->DestroyTexture(data->m_FontTexture);
    }

    ::ImGui::DestroyContext();
}

#include "TabiImGui.h"

#include "SequentialConversionTable.h"

#include <Math/mat4.h>

#include <IDevice.h>
#include <ICommandList.h>
#include <Texture.h>
#include <TextureUpdateDescription.h>
#include <GraphicsPipeline.h>
#include <Sampler.h>
#include <Buffer.h>

#include <Graphics.h>
#include <IWindow.h>

#include <InputManager.h>
#include <Helpers/KeyboardKeyToChar.h>

#include <imgui/imgui.h>

namespace tabi
{
    namespace imgui
    {

        class EMouseToImGuiTable : public SequentialConversionTable<EMouse, ::ImGuiMouseButton_, EMouse::Left, EMouse::Wheel>
        {
        public:
            EMouseToImGuiTable()
            {
                Add(EMouse::Left, ImGuiMouseButton_Left);
                Add(EMouse::Right, ImGuiMouseButton_Right);
                Add(EMouse::Middle, ImGuiMouseButton_Middle);
            }
        };

        class EKeyboardToImGuiTable : public SequentialConversionTable<EKeyboard, ::ImGuiKey, EKeyboard::A, EKeyboard::Pause>
        {
        public:
            EKeyboardToImGuiTable()
            {
                Add(EKeyboard::A, ::ImGuiKey_A);
                Add(EKeyboard::B, ::ImGuiKey_B);
                Add(EKeyboard::C, ::ImGuiKey_C);
                Add(EKeyboard::D, ::ImGuiKey_D);
                Add(EKeyboard::E, ::ImGuiKey_E);
                Add(EKeyboard::F, ::ImGuiKey_F);
                Add(EKeyboard::G, ::ImGuiKey_G);
                Add(EKeyboard::H, ::ImGuiKey_H);
                Add(EKeyboard::I, ::ImGuiKey_I);
                Add(EKeyboard::J, ::ImGuiKey_J);
                Add(EKeyboard::K, ::ImGuiKey_K);
                Add(EKeyboard::L, ::ImGuiKey_L);
                Add(EKeyboard::M, ::ImGuiKey_M);
                Add(EKeyboard::N, ::ImGuiKey_N);
                Add(EKeyboard::O, ::ImGuiKey_O);
                Add(EKeyboard::P, ::ImGuiKey_P);
                Add(EKeyboard::Q, ::ImGuiKey_Q);
                Add(EKeyboard::R, ::ImGuiKey_R);
                Add(EKeyboard::S, ::ImGuiKey_S);
                Add(EKeyboard::T, ::ImGuiKey_T);
                Add(EKeyboard::U, ::ImGuiKey_U);
                Add(EKeyboard::V, ::ImGuiKey_V);
                Add(EKeyboard::W, ::ImGuiKey_W);
                Add(EKeyboard::X, ::ImGuiKey_X);
                Add(EKeyboard::Y, ::ImGuiKey_Y);
                Add(EKeyboard::Z, ::ImGuiKey_Z);

                Add(EKeyboard::Minus, ::ImGuiKey_Minus);
                Add(EKeyboard::Equals, ::ImGuiKey_Equal);
                Add(EKeyboard::BracketLeft, ::ImGuiKey_LeftBracket);
                Add(EKeyboard::BracketRight, ::ImGuiKey_RightBracket);
                Add(EKeyboard::Semicolon, ::ImGuiKey_Semicolon);
                Add(EKeyboard::Apostrophe, ::ImGuiKey_Apostrophe);
                Add(EKeyboard::Comma, ::ImGuiKey_Comma);
                Add(EKeyboard::Period, ::ImGuiKey_Period);
                Add(EKeyboard::Slash, ::ImGuiKey_Slash);
                Add(EKeyboard::Backslash, ::ImGuiKey_Backslash);
                Add(EKeyboard::AccentGrave, ::ImGuiKey_GraveAccent);


                Add(EKeyboard::LeftCtrl, ::ImGuiKey_LeftCtrl);
                Add(EKeyboard::RightCtrl, ::ImGuiKey_RightCtrl);
                Add(EKeyboard::LeftAlt, ::ImGuiKey_LeftAlt);
                Add(EKeyboard::AltGr, ::ImGuiKey_RightAlt);
                Add(EKeyboard::LeftShift, ::ImGuiKey_LeftShift);
                Add(EKeyboard::RightShift, ::ImGuiKey_RightShift);
                Add(EKeyboard::Enter, ::ImGuiKey_Enter);
                Add(EKeyboard::Backspace, ::ImGuiKey_Backspace);
                Add(EKeyboard::Escape, ::ImGuiKey_Escape);
                Add(EKeyboard::Space, ::ImGuiKey_Space);
                Add(EKeyboard::Tab, ::ImGuiKey_Tab);
                Add(EKeyboard::ArrowUp, ::ImGuiKey_UpArrow);
                Add(EKeyboard::ArrowDown, ::ImGuiKey_DownArrow);
                Add(EKeyboard::ArrowLeft, ::ImGuiKey_LeftArrow);
                Add(EKeyboard::ArrowRight, ::ImGuiKey_RightArrow);

                Add(EKeyboard::Key0, ::ImGuiKey_0);
                Add(EKeyboard::Key1, ::ImGuiKey_1);
                Add(EKeyboard::Key2, ::ImGuiKey_2);
                Add(EKeyboard::Key3, ::ImGuiKey_3);
                Add(EKeyboard::Key4, ::ImGuiKey_4);
                Add(EKeyboard::Key5, ::ImGuiKey_5);
                Add(EKeyboard::Key6, ::ImGuiKey_6);
                Add(EKeyboard::Key7, ::ImGuiKey_7);
                Add(EKeyboard::Key8, ::ImGuiKey_8);
                Add(EKeyboard::Key9, ::ImGuiKey_9);

                Add(EKeyboard::Keypad0, ::ImGuiKey_Keypad0);
                Add(EKeyboard::Keypad1, ::ImGuiKey_Keypad1);
                Add(EKeyboard::Keypad2, ::ImGuiKey_Keypad2);
                Add(EKeyboard::Keypad3, ::ImGuiKey_Keypad3);
                Add(EKeyboard::Keypad4, ::ImGuiKey_Keypad4);
                Add(EKeyboard::Keypad5, ::ImGuiKey_Keypad5);
                Add(EKeyboard::Keypad6, ::ImGuiKey_Keypad6);
                Add(EKeyboard::Keypad7, ::ImGuiKey_Keypad7);
                Add(EKeyboard::Keypad8, ::ImGuiKey_Keypad8);
                Add(EKeyboard::Keypad9, ::ImGuiKey_Keypad9);
                Add(EKeyboard::KeypadPlus, ::ImGuiKey_KeypadAdd);
                Add(EKeyboard::KeypadMinus, ::ImGuiKey_KeypadSubtract);
                Add(EKeyboard::KeypadSlash, ::ImGuiKey_KeypadDivide);
                Add(EKeyboard::KeypadAsterisk, ::ImGuiKey_KeypadMultiply);
                Add(EKeyboard::KeypadPeriod, ::ImGuiKey_KeypadDecimal);
                Add(EKeyboard::KeypadEnter, ::ImGuiKey_KeypadEnter);

                Add(EKeyboard::F1, ::ImGuiKey_F1);
                Add(EKeyboard::F2, ::ImGuiKey_F2);
                Add(EKeyboard::F3, ::ImGuiKey_F3);
                Add(EKeyboard::F4, ::ImGuiKey_F4);
                Add(EKeyboard::F5, ::ImGuiKey_F5);
                Add(EKeyboard::F6, ::ImGuiKey_F6);
                Add(EKeyboard::F7, ::ImGuiKey_F7);
                Add(EKeyboard::F8, ::ImGuiKey_F8);
                Add(EKeyboard::F9, ::ImGuiKey_F9);
                Add(EKeyboard::F10, ::ImGuiKey_F10);
                Add(EKeyboard::F11, ::ImGuiKey_F11);
                Add(EKeyboard::F12, ::ImGuiKey_F12);

                Add(EKeyboard::Insert, ::ImGuiKey_Insert);
                Add(EKeyboard::Delete, ::ImGuiKey_Delete);
                Add(EKeyboard::Home, ::ImGuiKey_Home);
                Add(EKeyboard::End, ::ImGuiKey_End);
                Add(EKeyboard::PageUp, ::ImGuiKey_PageUp);
                Add(EKeyboard::PageDown, ::ImGuiKey_PageDown);
                Add(EKeyboard::PrintScreen, ::ImGuiKey_PrintScreen);
                Add(EKeyboard::ScrollLock, ::ImGuiKey_ScrollLock);
                Add(EKeyboard::Pause, ::ImGuiKey_Pause);
            }
        };

        class EControllerToImGuiTable : public SequentialConversionTable<EController, ::ImGuiKey, EController::DPadLeft, EController::MagneticFieldZ>
        {
        public:
            EControllerToImGuiTable()
            {
                Add(EController::DPadLeft, ::ImGuiKey_GamepadDpadLeft);
                Add(EController::DPadRight, ::ImGuiKey_GamepadDpadRight);
                Add(EController::DPadUp, ::ImGuiKey_GamepadDpadUp);
                Add(EController::DPadDown, ::ImGuiKey_GamepadDpadDown);
                Add(EController::FaceLeft, ::ImGuiKey_GamepadFaceLeft);
                Add(EController::FaceRight, ::ImGuiKey_GamepadFaceRight);
                Add(EController::FaceUp, ::ImGuiKey_GamepadFaceUp);
                Add(EController::FaceDown, ::ImGuiKey_GamepadFaceDown);
                Add(EController::SpecialLeft, ::ImGuiKey_GamepadStart);
                Add(EController::SpecialRight, ::ImGuiKey_GamepadBack);
                Add(EController::L1, ::ImGuiKey_GamepadL1);
                Add(EController::L3, ::ImGuiKey_GamepadL3);
                Add(EController::R1, ::ImGuiKey_GamepadR1);
                Add(EController::R3, ::ImGuiKey_GamepadR3);
                // Sticks and triggers are handled separately
            }
        };

        struct RenderContext
        {
            ICommandList* m_CommandList = nullptr;
            GraphicsPipeline* m_GraphicsPipeline = nullptr;
            Sampler* m_Sampler = nullptr;
            Texture* m_FontTexture = nullptr;

            Buffer* m_VertexBuffer = nullptr;
            Buffer* m_IndexBuffer = nullptr;
            Buffer* m_ConstantBuffer = nullptr;

            Shader* m_VertexShader = nullptr;
            Shader* m_PixelShader = nullptr;

            ~RenderContext()
            {
                auto* device = IDevice::GetInstance();
                device->DestroyCommandList(m_CommandList);
                device->DestroyGraphicsPipeline(m_GraphicsPipeline);
                device->DestroySampler(m_Sampler);
                device->DestroyBuffer(m_VertexBuffer);
                device->DestroyBuffer(m_IndexBuffer);
                device->DestroyBuffer(m_ConstantBuffer);
                device->DestroyShader(m_VertexShader);
                device->DestroyShader(m_PixelShader);
                device->DestroyTexture(m_FontTexture);
            }
        };

        struct ImGuiConstantBufferData
        {
            tabi::mat4 m_OrthoMatrix;
        };

        struct WindowSize
        {
            uint32_t m_WindowWidth = 0;
            uint32_t m_WindowHeight = 0;

            void Resize(WindowResizeEventData a_Data)
            {
                m_WindowWidth = a_Data.m_NewWidth;
                m_WindowHeight = a_Data.m_NewHeight;
            }
        };

        static WindowSize s_WindowSize;

        RenderContext* GetRenderContext()
        {
            return ImGui::GetCurrentContext() ? static_cast<RenderContext*>(ImGui::GetIO().BackendRendererUserData) : nullptr;
        }

        Buffer* CreateVertexBuffer(size_t a_Size)
        {
            return IDevice::GetInstance()->CreateBuffer({ EFormat::RG32_float, EBufferRole::Vertex, a_Size, sizeof(ImDrawVert) }, "ImGui vertices");
        }

        Buffer* CreateIndexBuffer(size_t a_Size)
        {
            return IDevice::GetInstance()->CreateBuffer({ sizeof(ImDrawIdx) == 2 ? EFormat::R16_uint : EFormat::R32_uint, EBufferRole::Index, a_Size, sizeof(ImDrawIdx) }, "ImGui indices");
        }

        void DestroyBuffer(Buffer*& a_Buffer)
        {
            IDevice::GetInstance()->DestroyBuffer(a_Buffer);
        }

        void InitRenderContext(RenderContext* a_Ctx)
        {
            auto* device = tabi::IDevice::GetInstance();
            auto& io = ::ImGui::GetIO();

            a_Ctx->m_CommandList = device->CreateCommandList("ImGui Commands");
            a_Ctx->m_CommandList->BeginRecording();

            int fontTextureWidth = 0;
            int fontTextureHeight = 0;
            unsigned char* pixels = nullptr;
            io.Fonts->GetTexDataAsRGBA32(&pixels, &fontTextureWidth, &fontTextureHeight);
            a_Ctx->m_FontTexture = device->CreateTexture(tabi::TextureDescription{ ETextureDimension::Tex2D, ETextureRole::Texture, EFormat::RGBA8_unorm, static_cast<uint64_t>(fontTextureWidth), static_cast<uint64_t>(fontTextureHeight), 1, 1 }, "ImGui Font");
            TextureUpdateDescription tud;
            tud.m_Data = pixels;
            tud.m_DataWidth = fontTextureWidth;
            tud.m_DataHeight = fontTextureHeight;

            a_Ctx->m_CommandList->CopyDataToTexture(a_Ctx->m_FontTexture, tud);
            io.Fonts->SetTexID(a_Ctx->m_FontTexture);

            a_Ctx->m_VertexShader = tabi::graphics::LoadShader("TabiAssets/Shaders/imgui.vert", EShaderType::Vertex, "ImGui vertex shader");
            a_Ctx->m_PixelShader = tabi::graphics::LoadShader("TabiAssets/Shaders/imgui.frag", EShaderType::Pixel, "ImGui pixel shader");

            GraphicsPipelineDescription gpd;
            gpd.m_VertexShader = a_Ctx->m_VertexShader;
            gpd.m_PixelShader = a_Ctx->m_PixelShader;
            gpd.m_Topology = EToplolgy::Triangle;

            gpd.m_IndividualBlend = false;
            gpd.m_BlendState[0].m_BlendEnabled = true;
            gpd.m_BlendState[0].m_BlendOperationRGB = EBlendOperation::Add;
            gpd.m_BlendState[0].m_BlendOperationAlpha = EBlendOperation::Add;
            gpd.m_BlendState[0].m_SourceBlendFactorRGB = EBlendFactor::SrcAlpha;
            gpd.m_BlendState[0].m_DestBlendFactorRGB = EBlendFactor::InvSrcAlpha;
            gpd.m_BlendState[0].m_SourceBlendFactorAlpha = EBlendFactor::One;
            gpd.m_BlendState[0].m_DestBlendFactorAlpha = EBlendFactor::InvSrcAlpha;

            gpd.m_RasterizerState.m_CullMode = ECullMode::None;
            gpd.m_RasterizerState.m_ScissorEnabled = true;

            gpd.m_DepthStencilState.m_FrontStencilState.m_StencilFunc = EComparisonFunction::Never;
            gpd.m_DepthStencilState.m_BackStencilState.m_StencilFunc = EComparisonFunction::Never;
            gpd.m_DepthStencilState.m_EnableDepthTest = false;

            gpd.m_VertexInputLayout.m_NumInputElements = 3;
            gpd.m_VertexInputLayout.m_InputElements[0] = VertexInputElement{ 0, 0, "POSITION", EFormat::RG32_float, EInstanceDataStepClassification::PerVertex, 0 };
            gpd.m_VertexInputLayout.m_InputElements[1] = VertexInputElement{ 0, 0, "TEXCOORD", EFormat::RG32_float, EInstanceDataStepClassification::PerVertex, 0 };
            gpd.m_VertexInputLayout.m_InputElements[2] = VertexInputElement{ 0, 0, "COLOR", EFormat::RGBA8_unorm, EInstanceDataStepClassification::PerVertex, 0 };

            a_Ctx->m_GraphicsPipeline = device->CreateGraphicsPipeline(gpd, "ImGui pipeline");

            a_Ctx->m_Sampler = device->CreateSampler({ EFilterMode::Linear, EFilterMode::Linear, tabi::EMipMapMode::Linear, tabi::EWrapMode::Clamp });
            a_Ctx->m_VertexBuffer = CreateVertexBuffer(2048 * sizeof(ImDrawVert));
            a_Ctx->m_IndexBuffer = CreateIndexBuffer(2048 * sizeof(ImDrawIdx));

            a_Ctx->m_ConstantBuffer = device->CreateBuffer({ EFormat::RGBA32_float, EBufferRole::Constant, sizeof(imgui::ImGuiConstantBufferData), 0 }, "ImGui cbuffer");

            a_Ctx->m_CommandList->EndRecording();
            device->ExecuteCommandList(a_Ctx->m_CommandList);

            const auto& window = tabi::graphics::IWindow::GetInstance();
            window.GetWindowDimensions(s_WindowSize.m_WindowWidth, s_WindowSize.m_WindowHeight);
            window.OnWindowResize().Subscribe(&s_WindowSize, &WindowSize::Resize);
        }

        void UpdateMouseCursor()
        {
            const auto& io = ImGui::GetIO();

            if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
            {
                return;
            }

            const ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
            if (imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor)
            {
                tabi::InputManager::SetCursorVisible(false);
            }
        }

        void UpdateMouseData()
        {
            static EMouseToImGuiTable MouseTable;

            auto& io = ImGui::GetIO();

            for(uint32_t i = 0; i < MouseTable.m_NumEntries; ++i)
            {
                const auto key = MouseTable.Get(i);
                if(key != MouseTable.m_InvalidEntry)
                {
                    io.AddMouseButtonEvent(key, tabi::InputManager::IsButtonDownRaw(static_cast<EMouse>(i + MouseTable.m_FirstEntryValue)));
                }
            }

            const auto mx = tabi::InputManager::GetAxisValueRaw(EMouse::MouseX);
            const auto my = tabi::InputManager::GetAxisValueRaw(EMouse::MouseY);
            // TODO: Should maybe be something like -FLT_MAX when the window has no focus
            io.AddMousePosEvent(mx, my);

            float wheelDelta = 0.0f;
            tabi::InputManager::GetAxisValueRaw(EMouse::Wheel, &wheelDelta);
            io.AddMouseWheelEvent(0.0f, wheelDelta);
        }

        void UpdateKeyboard()
        {
            static EKeyboardToImGuiTable KeyboardTable;

            const bool shiftIsDown = tabi::InputManager::IsButtonDownRaw(EKeyboard::Shift);

            auto& io = ImGui::GetIO();

            for (uint32_t i = 0; i < KeyboardTable.m_NumEntries; ++i)
            {
                const auto key = KeyboardTable.Get(i);
                if (key != KeyboardTable.m_InvalidEntry)
                {
                    bool wasDown = false;
                    const bool isDown = tabi::InputManager::IsButtonDownRaw(static_cast<EKeyboard>(i + KeyboardTable.m_FirstEntryValue), &wasDown);

                    if(wasDown != isDown)
                    {
                        io.AddKeyEvent(key, isDown);

                        if(isDown)
                        {
                            const auto& charInfo = KeyboardToCharTable.Get(i);
                            if (charInfo.m_Char != 0)
                            {
                                if (shiftIsDown)
                                {
                                    io.AddInputCharacter(charInfo.m_Shift);
                                }
                                else
                                {
                                    io.AddInputCharacter(charInfo.m_Char);
                                }
                            }
                        }
                    }
                }
            }
        }

        void UpdateGamepad()
        {
            static EControllerToImGuiTable ControllerTable;

            auto& io = ImGui::GetIO();

            // Update buttons
            for (uint32_t i = 0; i < ControllerTable.m_NumEntries; ++i)
            {
                const auto key = ControllerTable.Get(i);
                if (key != ControllerTable.m_InvalidEntry)
                {
                    io.AddKeyEvent(key, tabi::InputManager::IsButtonDownRaw(static_cast<EController>(i + ControllerTable.m_FirstEntryValue)));
                }
            }

            // When this value is exceeded, consider the stick to be "pressed"
            static constexpr float AxisInputThreshold = 0.1f;

            // Update axes
            float current = tabi::InputManager::GetAxisValueRaw(EController::LeftStickX);
            io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickLeft, current < -AxisInputThreshold, std::clamp(-current, 0.0f, 1.0f));
            io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickRight, current > AxisInputThreshold, std::clamp(current, 0.0f, 1.0f));

            current = tabi::InputManager::GetAxisValueRaw(EController::LeftStickY);
            io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickUp, current > AxisInputThreshold, std::clamp(current, 0.0f, 1.0f));
            io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickDown, current < -AxisInputThreshold, std::clamp(-current, 0.0f, 1.0f));

            current = tabi::InputManager::GetAxisValueRaw(EController::RightStickX);
            io.AddKeyAnalogEvent(ImGuiKey_GamepadRStickLeft, current < -AxisInputThreshold, std::clamp(-current, 0.0f, 1.0f));
            io.AddKeyAnalogEvent(ImGuiKey_GamepadRStickRight, current > AxisInputThreshold, std::clamp(current, 0.0f, 1.0f));

            current = tabi::InputManager::GetAxisValueRaw(EController::RightStickY);
            io.AddKeyAnalogEvent(ImGuiKey_GamepadRStickUp, current > AxisInputThreshold, std::clamp(current, 0.0f, 1.0f));
            io.AddKeyAnalogEvent(ImGuiKey_GamepadRStickDown, current < -AxisInputThreshold, std::clamp(-current, 0.0f, 1.0f));

            current = tabi::InputManager::GetAxisValueRaw(EController::L2);
            io.AddKeyAnalogEvent(ImGuiKey_GamepadL2, current > AxisInputThreshold, std::clamp(current, 0.0f, 1.0f));

            current = tabi::InputManager::GetAxisValueRaw(EController::R2);
            io.AddKeyAnalogEvent(ImGuiKey_GamepadR2, current > AxisInputThreshold, std::clamp(current, 0.0f, 1.0f));
        }

    }
}

void tabi::imgui::Init()
{
    ::ImGui::CreateContext();
    auto& io = ::ImGui::GetIO();

    auto* renderContext = new RenderContext;
    InitRenderContext(renderContext);

    io.BackendRendererUserData = static_cast<void*>(renderContext);
    io.BackendRendererName = "imgui_impl_tabi";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    io.BackendPlatformName = "imgui_impl_tabi";

#if defined(_WIN32)
    const auto& window = tabi::graphics::IWindow::GetInstance();
    ImGui::GetMainViewport()->PlatformHandleRaw = window.GetHandle();
#endif
}

void tabi::imgui::NewFrame(float a_DeltaTime)
{
    auto& io = ::ImGui::GetIO();
    io.DeltaTime = a_DeltaTime;
    io.DisplaySize.x = s_WindowSize.m_WindowWidth;
    io.DisplaySize.y = s_WindowSize.m_WindowHeight;

    UpdateMouseCursor();
    UpdateMouseData();
    UpdateKeyboard();
    UpdateGamepad();

    ::ImGui::NewFrame();
}

namespace tabi
{
    namespace imgui
    {
        void SetUpRenderState(const ImDrawData* a_DrawData, int32_t a_FrameBufferWidth, int32_t a_FrameBufferheight)
        {
            const auto* ctx = GetRenderContext();
            TABI_ASSERT(ctx);

            ctx->m_CommandList->SetViewport(0, 0, a_FrameBufferWidth, a_FrameBufferheight);

            const float L = a_DrawData->DisplayPos.x;
            const float R = a_DrawData->DisplayPos.x + a_DrawData->DisplaySize.x;
            const float T = a_DrawData->DisplayPos.y;
            const float B = a_DrawData->DisplayPos.y + a_DrawData->DisplaySize.y;

            ImGuiConstantBufferData bufferData;
            bufferData.m_OrthoMatrix = tabi::mat4(
                2.0f / (R - L), 0.0f, 0.0f, 0.0f,
                0.0f, 2.0f / (T - B), 0.0f, 0.0f,
                0.0f, 0.0f, -1.0f, 0.0f,
                (R + L) / (L - R), (T + B) / (B - T), 0.0f, 1.0f
            );

            ctx->m_CommandList->CopyDataToBuffer(ctx->m_ConstantBuffer, &bufferData, sizeof(ImGuiConstantBufferData));

            ctx->m_CommandList->UseGraphicsPipeline(ctx->m_GraphicsPipeline);

            ctx->m_CommandList->BindSampler(ctx->m_Sampler, 0);

            ctx->m_CommandList->BindVertexBuffers(0, &ctx->m_VertexBuffer, 1);
            ctx->m_CommandList->BindIndexBuffer(ctx->m_IndexBuffer);
            ctx->m_CommandList->BindConstantBuffer(ctx->m_ConstantBuffer, 0);
        }
    }
}

void tabi::imgui::EndFrame()
{
    ::ImGui::EndFrame();
    ::ImGui::Render();

    const ImDrawData* drawData = ::ImGui::GetDrawData();

    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    const int32_t fbWidth = static_cast<int>(drawData->DisplaySize.x * drawData->FramebufferScale.x);
    const int32_t fbHeight = static_cast<int>(drawData->DisplaySize.y * drawData->FramebufferScale.y);
    if (fbWidth <= 0 || fbHeight <= 0)
        return;

    auto* ctx = GetRenderContext();
    TABI_ASSERT(ctx);

    ctx->m_CommandList->BeginRecording();
    // Draw to the screen directly
    ctx->m_CommandList->SetRenderTarget(nullptr);

    SetUpRenderState(drawData, fbWidth, fbHeight);

    const ImVec2 clipOffset = drawData->DisplayPos;
    const ImVec2 clipScale = drawData->FramebufferScale;

    for (size_t i = 0; i < drawData->CmdListsCount; ++i)
    {
        const ImDrawList* drawList = drawData->CmdLists[i];

        const size_t vertexBufferDataSize = static_cast<size_t>(drawList->VtxBuffer.Size) * sizeof(ImDrawVert);
        const size_t indexBufferDataSize = static_cast<size_t>(drawList->IdxBuffer.Size) * sizeof(ImDrawIdx);
        if (ctx->m_VertexBuffer->GetBufferSize() < vertexBufferDataSize)
        {
            DestroyBuffer(ctx->m_VertexBuffer);
            ctx->m_VertexBuffer = CreateVertexBuffer(vertexBufferDataSize);
        }
        if (ctx->m_IndexBuffer->GetBufferSize() < indexBufferDataSize)
        {
            DestroyBuffer(ctx->m_IndexBuffer);
            ctx->m_IndexBuffer = CreateIndexBuffer(indexBufferDataSize);
        }
        ctx->m_CommandList->CopyDataToBuffer(ctx->m_VertexBuffer, drawList->VtxBuffer.Data, vertexBufferDataSize, 0);
        ctx->m_CommandList->CopyDataToBuffer(ctx->m_IndexBuffer, drawList->IdxBuffer.Data, indexBufferDataSize, 0);

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
                const ImVec2 clipMin((cmd->ClipRect.x - clipOffset.x) * clipScale.x, (cmd->ClipRect.y - clipOffset.y) * clipScale.y);
                const ImVec2 clipMax((cmd->ClipRect.z - clipOffset.x) * clipScale.x, (cmd->ClipRect.w - clipOffset.y) * clipScale.y);
                if (clipMax.x <= clipMin.x || clipMax.y <= clipMin.y)
                    continue;

                ctx->m_CommandList->SetScissorRect(static_cast<int32_t>(clipMin.x), static_cast<int32_t>(clipMin.y), 
                    static_cast<int32_t>(clipMax.x - clipMin.x), static_cast<int32_t>(clipMax.y - clipMin.y));

                ctx->m_CommandList->BindTexture(static_cast<Texture*>(cmd->GetTexID()), 0);
                ctx->m_CommandList->DrawIndexed(cmd->ElemCount, cmd->IdxOffset, cmd->VtxOffset);
            }
        }
    }

    ctx->m_CommandList->EndRecording();
    IDevice::GetInstance()->ExecuteCommandList(ctx->m_CommandList);
    ctx->m_CommandList->Reset();
}

void tabi::imgui::Shutdown()
{
    auto* renderContext = GetRenderContext();
    if (renderContext)
    {
        delete renderContext;
    }
    
    ::ImGui::DestroyContext();
}

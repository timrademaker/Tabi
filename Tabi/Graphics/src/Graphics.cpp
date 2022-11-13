#include "Graphics.h"

#include "IWindow.h"

#include <ICommandList.h>
#include <IDevice.h>
#include <Shader.h>
#include <Enums/ShaderEnums.h>

#include <IFile.h>

#include <Logging.h>

#include "Texture.h"
#include "TextureUpdateDescription.h"
void tabi::graphics::BeginFrame()
{
    auto* device = IDevice::GetInstance();
    auto* cmd = device->CreateCommandList("BeginFrame");
    cmd->BeginRecording();

    // Bind default render target and clear its color- and stencil values
    cmd->SetRenderTarget(nullptr);
    static constexpr float clearColor[] = { 0.109f, 0.4218f, 0.8984f, 1.0f };
    cmd->ClearRenderTarget(nullptr, clearColor);
    cmd->ClearDepthStencil(nullptr);

    cmd->EndRecording();
    device->ExecuteCommandList(cmd);
    device->DestroyCommandList(cmd);

    device->BeginFrame();
}

void tabi::graphics::EndFrame()
{
    auto* device = IDevice::GetInstance();
    device->EndFrame();
    device->Present();
}

tabi::Shader* tabi::graphics::LoadShader(const char* a_ShaderPath, tabi::EShaderType a_ShaderType, const char* a_DebugName)
{
    TABI_ASSERT(a_ShaderPath != nullptr);

    const auto shaderFile = tabi::IFile::OpenFile(a_ShaderPath, tabi::EFileOpenFlags::Read);
    tabi::vector<char> shaderContent;

    if (shaderFile)
    {
        tabi::FSize fileLen = 0;
        shaderFile->GetLength(fileLen);
        shaderContent.resize(fileLen + 1);

        const auto result = shaderFile->Read(&shaderContent[0], fileLen);
        if (!tabi::IFile::IsSuccess(result))
        {
            TABI_ERROR("Unable to read content from shader \"%s\"", a_ShaderPath);
            shaderFile->Close();
            return nullptr;
        }

        shaderFile->Close();

        if(a_DebugName == nullptr)
        {
            a_DebugName = a_ShaderPath;
        }

        return tabi::IDevice::GetInstance()->CreateShader(tabi::ShaderDescription{ a_ShaderType, shaderContent.data(), shaderContent.size() }, a_DebugName);
    }

    TABI_ERROR("Unable to read content from shader \"%s\"", a_ShaderPath);
    TABI_ASSERT(false);
    return nullptr;
}

tabi::Texture* tabi::LoadTexture(EFormat a_Format, ETextureDimension a_Dimension, uint64_t a_Width, uint64_t a_Height, uint16_t a_Depth, const void* a_Data, const char* a_DebugName)
{
    auto* device = IDevice::GetInstance();
    auto* cmd = device->CreateCommandList("LoadTexture");
    cmd->BeginRecording();

    auto* tex = device->CreateTexture(TextureDescription{ a_Dimension, ETextureRole::Texture, a_Format, a_Width, a_Height, a_Depth, 1}, a_DebugName);

    TextureUpdateDescription tud;
    tud.m_Data = a_Data;
    tud.m_DataWidth = a_Width;
    tud.m_DataHeight = a_Height;
    tud.m_DataDepth = a_Depth;
    tud.m_MipLevel = 0;
    cmd->CopyDataToTexture(tex, tud);

    cmd->EndRecording();
    device->ExecuteCommandList(cmd);
    device->DestroyCommandList(cmd);

    return tex;
}

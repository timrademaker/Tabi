#include "Graphics.h"

#include "IWindow.h"

#include <ICommandList.h>
#include <IDevice.h>
#include <Shader.h>
#include <Enums/ShaderEnums.h>

#include <IFile.h>

#include <Logging.h>

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

        auto result = shaderFile->Read(&shaderContent[0], fileLen);
        if (!tabi::IFile::IsSuccess(result))
        {
            TABI_ERROR("Unable to read content from shader \"%s\"", a_ShaderPath);
            shaderFile->Close();
            return nullptr;
        }

        shaderFile->Close();

        return tabi::IDevice::GetInstance()->CreateShader(tabi::ShaderDescription{ a_ShaderType, shaderContent.data(), shaderContent.size() }, a_DebugName);
    }

    TABI_ERROR("Unable to read content from shader \"%s\"", a_ShaderPath);
    TABI_ASSERT(false);
    return nullptr;
}

#include "Graphics.h"

#include <IDevice.h>
#include <Shader.h>
#include <Enums/ShaderEnums.h>

#include <IFile.h>

#include <Logging.h>

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

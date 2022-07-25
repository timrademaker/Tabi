#include "IShader.h"

#include "IRenderer.h"

#if defined(_WINDOWS)
#include "Windows/OpenGL/OpenGLShader.h"
#endif

#include <TabiMacros.h>
#include <Logging.h>

#include <IFile.h>

tabi::IShader* tabi::IShader::CreateShader(const char* a_VertexShaderPath, const char* a_FragmentShaderPath)
{
    if (!tabi::graphics::IRenderer::GetInstance().HasBeenInitialized())
    {
        TABI_ERROR("Please initialize the renderer before trying to create a shader!");
        return nullptr;
    }

    tabi::vector<char> vertexShader;
    if (!tabi::IShader::LoadShaderContent(a_VertexShaderPath, vertexShader))
    {
        return nullptr;
    }

    tabi::vector<char> fragmentShader;
    if (!tabi::IShader::LoadShaderContent(a_FragmentShaderPath, fragmentShader))
    {
        return nullptr;
    }

    IShader* shader = new Shader;
    if (!shader->Initialize(&vertexShader[0], vertexShader.size(), &fragmentShader[0], fragmentShader.size()))
    {
        TABI_ERROR("Failed to create shader from vertex shader \"%s\" and fragment shader \"%s\"!", a_VertexShaderPath, a_FragmentShaderPath);
        return nullptr;
    }

    return shader;
}

tabi::shared_ptr<tabi::IShader> tabi::IShader::CreateSharedShader(const char* a_VertexShader, const char* a_FragmentShader)
{
    IShader* shader = IShader::CreateShader(a_VertexShader, a_FragmentShader);
    return ToShared(shader);
}

tabi::IShader* tabi::IShader::CreateShader(const char* a_VertexShaderString, const size_t a_VertexShaderLength, const char* a_FragmentShaderString, const size_t a_FragmentShaderLength)
{
    if (!tabi::graphics::IRenderer::GetInstance().HasBeenInitialized())
    {
        TABI_ERROR("Please initialize the renderer before trying to create a shader!");
        return nullptr;
    }

    IShader* shader = new Shader;
    if (!shader->Initialize(a_VertexShaderString, a_VertexShaderLength, a_FragmentShaderString, a_FragmentShaderLength))
    {
        delete shader;
        shader = nullptr;

        TABI_ERROR("Failed to create shader!");
    }

    return shader;
}

tabi::shared_ptr<tabi::IShader> tabi::IShader::CreateSharedShader(const char* a_VertexShaderString, const size_t a_VertexShaderLength, const char* a_FragmentShaderString, const size_t a_FragmentShaderLength)
{
    IShader* shader = IShader::CreateShader(a_VertexShaderString, a_VertexShaderLength, a_FragmentShaderString, a_FragmentShaderLength);
    return ToShared(shader);
}

tabi::shared_ptr<tabi::IShader> tabi::IShader::ToShared(IShader*& a_Rhs)
{
    TABI_ASSERT(a_Rhs);
    auto shared = tabi::shared_ptr<tabi::IShader>(static_cast<tabi::Shader*>(a_Rhs));
    a_Rhs = nullptr;
    return shared;
}

bool tabi::IShader::LoadShaderContent(const char* a_ShaderPath, tabi::vector<char>& a_Content)
{
    a_Content.clear();
    
    FSize fileLen = 0;

    // Load vertex shader
    auto shaderFile = IFile::OpenFile(a_ShaderPath, EFileOpenFlags::Read);

    if (shaderFile)
    {
        shaderFile->GetLength(fileLen);
        a_Content = tabi::vector<char>(fileLen);
        auto result = shaderFile->Read(&a_Content[0], fileLen);
        if (!IFile::IsSuccess(result))
        {
            TABI_ERROR("Unable to read content from shader \"%s\"", a_ShaderPath);
            shaderFile->Close();
            return false;
        }

        shaderFile->Close();
    }
    else
    {
        TABI_ERROR("Unable to read content from shader \"%s\"", a_ShaderPath);
        return false;
    }

    return true;
}
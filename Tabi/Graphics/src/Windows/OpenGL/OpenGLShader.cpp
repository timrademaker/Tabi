#include "Windows/OpenGL/OpenGLShader.h"

#include "IRenderer.h"
#include "Windows/OpenGL/OpenGLHelpers.h"

#include <Math/vec4.h>
#include <Math/mat4.h>

#include <Logging.h>

#include <glad/glad.h>

bool tabi::Shader::UseShader()
{
    if (!tabi::graphics::IRenderer::GetInstance().HasBeenInitialized())
    {
        TABI_ERROR("Please initialize the renderer before trying to use a shader!");
        return false;
    }
    
    glUseProgram(m_ShaderProgram);

    return !tabi::graphics::helpers::CheckForErrors();
}

bool tabi::Shader::SetUniformInt(const char* a_UniformName, const int a_Value)
{
    const int loc = GetUniformLocation(a_UniformName);

    glUniform1i(loc, a_Value);

    return !tabi::graphics::helpers::CheckForErrors();
}

bool tabi::Shader::SetUniformVec4f(const char* a_UniformName, const int a_Count, const tabi::vec4* a_Value)
{
    const int loc = GetUniformLocation(a_UniformName);    
    glUniform4fv(loc, a_Count, &a_Value->v[0]);

    return !tabi::graphics::helpers::CheckForErrors();
}

bool tabi::Shader::SetUniformMat4f(const char* a_UniformName, const int a_Count, bool a_Transpose, const tabi::mat4* a_Value)
{
    const int loc = GetUniformLocation(a_UniformName);
    glUniformMatrix4fv(loc, a_Count, a_Transpose, &a_Value->v[0]);

    return !tabi::graphics::helpers::CheckForErrors();
}

bool tabi::Shader::Initialize(const char* a_VertexShaderString, const size_t a_VertexShaderLength, const char* a_FragmentShaderString, const size_t a_FragmentShaderLength)
{
    if (!tabi::graphics::IRenderer::GetInstance().HasBeenInitialized())
    {
        TABI_ERROR("Please initialize the renderer before trying to create a shader!");
        return false;
    }

    // Load vertex shader
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    int vShadLen = static_cast<int>(a_VertexShaderLength);
    glShaderSource(vertexShader, 1, &a_VertexShaderString, &vShadLen);
    glCompileShader(vertexShader);
    tabi::graphics::helpers::CheckShaderLoadSuccess(vertexShader);

    // Load fragment shader
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    int fShadLen = static_cast<int>(a_FragmentShaderLength);
    glShaderSource(fragmentShader, 1, &a_FragmentShaderString, &fShadLen);
    glCompileShader(fragmentShader);
    tabi::graphics::helpers::CheckShaderLoadSuccess(fragmentShader);

    // Create shader program
    m_ShaderProgram = glCreateProgram();
    glAttachShader(m_ShaderProgram, vertexShader);
    glAttachShader(m_ShaderProgram, fragmentShader);
    glLinkProgram(m_ShaderProgram);

    // Delete loaded shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return tabi::graphics::helpers::CheckShaderProgramSuccess(m_ShaderProgram);
}


int tabi::Shader::GetUniformLocation(const char* a_UniformName)
{
    auto iter = m_KnownUniformLocations.find(a_UniformName);
    if (iter != m_KnownUniformLocations.end())
    {
        return iter->second;
    }
    else
    {
        const GLint loc = glGetUniformLocation(m_ShaderProgram, a_UniformName);   
        m_KnownUniformLocations.emplace(tabi::make_pair(a_UniformName, loc));

        tabi::graphics::helpers::CheckForErrors();
        return loc;
    }
}


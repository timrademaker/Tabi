#include "Windows/OpenGL/OpenGLRenderer.h"

#include "Windows/OpenGL/OpenGLHelpers.h"
#include <TabiMacros.h>

#include <IFile.h>
#include <Resources/Mesh.h>
#include <Resources/Texture.h>
#include <Resources/Material.h>

#include "Logging.h"

#include <glad/glad.h>

#include <cassert>

using namespace tabi::graphics;

tabi::graphics::Renderer::Renderer()
{
    if(!helpers::IsOpenGLVersionSupported(MINIMUM_OGL_VERSION))
    {
        assert(false);
    }

    // Load shaders
    m_MeshShader = CreateShaderProgram("TabiAssets/Shaders/VertexShader.vert", "TabiAssets/Shaders/FragmentShader.frag");
    m_TextureShader = CreateShaderProgram("TabiAssets/Shaders/SingleTextureShader.vert", "TabiAssets/Shaders/SingleTextureShader.frag");
    UseShader(m_TextureShader);


    // Create and set (default) texture sampler params
    glGenSamplers(1, &m_TextureSampler);
    glBindSampler(0, m_TextureSampler);

    // Wrapping mode
    glSamplerParameteri(m_TextureSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glSamplerParameteri(m_TextureSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // Border color
    const float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glSamplerParameterfv(m_TextureSampler, GL_TEXTURE_BORDER_COLOR, borderColor);
    // Filtering
    glSamplerParameteri(m_TextureSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glSamplerParameteri(m_TextureSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

bool tabi::graphics::Renderer::BufferMesh(Mesh& a_Mesh, const bool a_CleanUpMeshDataAfterBuffering, EBufferMode a_BufferMode) const
{
    assert(!a_Mesh.m_Vertices.empty());

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLuint ebo = 0;
    if (!a_Mesh.m_Indices.empty())
    {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    }

    GLenum usage = GL_STATIC_DRAW;
    switch (a_BufferMode)
    {
    case EBufferMode::Dynamic:
    {
        usage = GL_DYNAMIC_DRAW;
        break;
    }
    case EBufferMode::Stream:
    {
        usage = GL_STREAM_DRAW;
        break;
    }
    default:
        break;
    }

    glBufferData(GL_ARRAY_BUFFER, a_Mesh.m_Vertices.size() * sizeof(Mesh::Vertex), &a_Mesh.m_Vertices[0], usage);

    // Vertex coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Vertex normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    if (!a_Mesh.m_Indices.empty())
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_Mesh.m_Indices.size() * sizeof(a_Mesh.m_Indices.at(0)), &a_Mesh.m_Indices[0], usage);
    }

    if(!a_Mesh.m_Indices.empty())
    {
        a_Mesh.m_VertexCount = static_cast<unsigned int>(a_Mesh.m_Indices.size());
    }
    else
    {
        a_Mesh.m_VertexCount = static_cast<unsigned int>(a_Mesh.m_Vertices.size());
    }
    
    a_Mesh.m_VAO = vao;
    a_Mesh.m_VBO = vbo;
    a_Mesh.m_EBO = ebo;
    
    if (a_CleanUpMeshDataAfterBuffering)
    {
        a_Mesh.m_Vertices.clear();
        a_Mesh.m_Indices.clear();
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Check for textures to buffer
    if (a_Mesh.m_Material
        && a_Mesh.m_Material->m_MetalicRoughness
        && a_Mesh.m_Material->m_MetalicRoughness->m_BaseColorTexture
        )
    {
        BufferTexture(*a_Mesh.m_Material->m_MetalicRoughness->m_BaseColorTexture.get());
    }

    return true;
}

bool tabi::graphics::Renderer::BufferTexture(Texture& a_Texture, const bool a_CleanUpTextureDataAfterBuffering) const
{
    // TODO: Store color mode in texture (RGB(A))
    // TODO: Support 1D and 3D textures as well?

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, a_Texture.m_Width, a_Texture.m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &a_Texture.m_TextureData[0]);
    glGenerateMipmap(GL_TEXTURE_2D);


    a_Texture.m_TextureHandle = tex;

    if (a_CleanUpTextureDataAfterBuffering)
    {
        a_Texture.m_TextureData.clear();
    }

    return true;
}

ShaderHandle tabi::graphics::Renderer::CreateShaderProgram(const char* a_VertexShader, const int a_VertexShaderLength, const char* a_FragmentShader, const int a_FragmentShaderLength) const
{
    // Load vertex shader
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &a_VertexShader, &a_VertexShaderLength);
    glCompileShader(vertexShader);
    helpers::CheckShaderLoadError(vertexShader);

    // Load fragment shader
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &a_FragmentShader, &a_FragmentShaderLength);
    glCompileShader(fragmentShader);
    helpers::CheckShaderLoadError(fragmentShader);

    // Create shader program
    ShaderHandle program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    helpers::CheckShaderProgramError(program);

    // Delete loaded shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

ShaderHandle tabi::graphics::Renderer::CreateShaderProgram(const char* a_VertexShaderPath, const char* a_FragmentShaderPath) const
{
    FSize fileLen = 0;

    // Load vertex shader
    auto vertShadFile = IFile::OpenFile(a_VertexShaderPath, EFileOpenFlags::Read);
    FSize vertShaderBytesRead = 0;
    vertShadFile->GetLength(fileLen);
    
    tabi::vector<char> vertexShaderBuffer(fileLen);
    vertShadFile->Read(&vertexShaderBuffer[0], fileLen, &vertShaderBytesRead);

    // Load fragment shader
    auto fragShadFile = IFile::OpenFile(a_FragmentShaderPath, EFileOpenFlags::Read);
    FSize fragShaderBytesRead = 0;
    fragShadFile->GetLength(fileLen);

    tabi::vector<char> fragmentShaderBuffer(fileLen);
    fragShadFile->Read(&fragmentShaderBuffer[0], fileLen, &fragShaderBytesRead);

    logger::TabiLog(logger::ELogLevel::Info, tabi::string(&vertexShaderBuffer[0]));
    logger::TabiLog(logger::ELogLevel::Info, tabi::string(&fragmentShaderBuffer[0]));

    return CreateShaderProgram(&vertexShaderBuffer[0], static_cast<int>(vertShaderBytesRead), &fragmentShaderBuffer[0], static_cast<int>(fragShaderBytesRead));
}

void Renderer::UseShader(const ShaderHandle a_ShaderHandle)
{
    glUseProgram(a_ShaderHandle);
    m_CurrentlyBoundShader = a_ShaderHandle;
}

void tabi::graphics::Renderer::RenderMesh(const Mesh& a_Mesh)
{
    // Bind texture if the mesh has one
    if (a_Mesh.m_Material
        && a_Mesh.m_Material->m_MetalicRoughness
        && a_Mesh.m_Material->m_MetalicRoughness->m_BaseColorTexture
        )
    {

        if (m_CurrentlyBoundShader != m_TextureShader)
        {
            UseShader(m_TextureShader);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, a_Mesh.m_Material->m_MetalicRoughness->m_BaseColorTexture->m_TextureHandle);
        glUniform1i(glGetUniformLocation(m_TextureShader, "uTexture"), 0);

        
    }
    else
    {
        if (m_CurrentlyBoundShader != m_MeshShader)
        {
            UseShader(m_MeshShader);
        }
    }

    glBindVertexArray(a_Mesh.m_VAO);
    if (a_Mesh.m_EBO != 0)
    {
        glDrawElements(GL_TRIANGLES, a_Mesh.m_VertexCount, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, a_Mesh.m_VertexCount);
    }
    glBindVertexArray(0);

    helpers::CheckForErrors();
}

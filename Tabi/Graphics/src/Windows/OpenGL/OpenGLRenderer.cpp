#include "Windows/OpenGL/OpenGLRenderer.h"

#include "Windows/OpenGL/OpenGLHelpers.h"
#include "TabiMacros.h"

#include <glad/glad.h>

#include <cassert>

using namespace tabi::graphics;

// Temporary mesh class for testing
class tabi::Mesh
{
public:
    struct Vertex
    {
        float m_Pos[3];
        float m_Normal[3];
        float m_TexCoords[2];
    };

public:
    tabi::vector<Vertex> m_Vertices;
    tabi::vector<unsigned int> m_Indices;
    tabi::vector<Texture> m_Textures;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

// Temporary texture class for testing
class tabi::Texture
{

};


MeshHandle tabi::graphics::Renderer::BufferMesh(const Mesh& a_Mesh, const EBufferMode a_BufferMode) const
{
    MeshHandle buff;
    glGenBuffers(1, &buff);
    glBindBuffer(GL_ARRAY_BUFFER, buff);


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
    }

    glBufferData(GL_ARRAY_BUFFER, a_Mesh.m_Vertices.size() * sizeof(Mesh::Vertex), &a_Mesh.m_Vertices[0], usage);
    helpers::CheckMeshLoadError(buff);

    return buff;
}

TextureHandle tabi::graphics::Renderer::BufferTexture(const Texture& a_Texture, const EBufferMode a_BufferMode) const
{
    TABI_UNUSED(a_Texture);
    TABI_UNUSED(a_BufferMode);

    // TODO: Implement
    assert(false);

    return TextureHandle();
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
    TABI_UNUSED(a_VertexShaderPath);
    TABI_UNUSED(a_FragmentShaderPath);

    // TODO: Implement
    assert(false);
    return ShaderHandle();
}
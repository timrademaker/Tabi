#include "Windows/OpenGL/OpenGLRenderer.h"

#include "ISampler.h"
#include "IShader.h"
#include "Windows/OpenGL/OpenGLHelpers.h"

#include "Camera.h"

#include <TabiMacros.h>

#include <IFile.h>
#include <Resources/Mesh.h>
#include <Resources/Texture.h>
#include <Resources/Material.h>

#include <Logging.h>

#include <glad/glad.h>

#include <cassert>

using namespace tabi::graphics;
using tabi::ISampler;

tabi::graphics::Renderer::Renderer()
{
    // Create a default camera
    m_CurrentCamera = tabi::make_shared<Camera>();
}

void tabi::graphics::Renderer::Initialize(tabi::shared_ptr<IWindow> a_Window)
{
    if (m_Initialized)
    {
        logger::TabiWarn("Renderer already initialized!");
        return;
    }

    m_Initialized = true;

    IRenderer::Initialize(a_Window);

    if (!helpers::IsOpenGLVersionSupported(MINIMUM_OGL_VERSION))
    {
        assert(false);
    }

    // Load shaders
    m_MeshShader = IShader::CreateSharedShader("TabiAssets/Shaders/VertexShader.vert", "TabiAssets/Shaders/FragmentShader.frag");
    m_TextureShader = IShader::CreateSharedShader("TabiAssets/Shaders/SingleTextureShader.vert", "TabiAssets/Shaders/SingleTextureShader.frag");
    UseShader(m_TextureShader);

    glEnable(GL_DEPTH_TEST);

    m_TextureSampler = ISampler::CreateSharedSampler(EWrap::ClampToEdge, EWrap::ClampToEdge, EMinFilter::LinearMipmapLinear, EMagFilter::Linear);
    UseSampler(m_TextureSampler);

}

bool tabi::graphics::Renderer::BufferMesh(Mesh& a_Mesh, const bool a_CleanUpMeshDataAfterBuffering, EBufferMode a_BufferMode) const
{
    if (!m_Initialized)
    {
        tabi::logger::TabiError("Please initialize the renderer before trying to buffer a mesh!");
        return false;
    }

    if (a_Mesh.m_VBO != 0)
    {
        // Mesh already loaded
        return false;
    }
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)offsetof(Mesh::Vertex, m_Normal));
    glEnableVertexAttribArray(1);

    // Texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)offsetof(Mesh::Vertex, m_TexCoords));
    glEnableVertexAttribArray(2);

    if (!a_Mesh.m_Indices.empty())
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_Mesh.m_Indices.size() * sizeof(unsigned int), &a_Mesh.m_Indices[0], usage);
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
    if (!m_Initialized)
    {
        tabi::logger::TabiError("Please initialize the renderer before trying to buffer a texture!");
        return false;
    }

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

void tabi::graphics::Renderer::RenderMesh(const Mesh& a_Mesh, const mat4& a_Transform)
{
    if (!m_Initialized)
    {
        tabi::logger::TabiError("Please initialize the renderer before trying to render!");
        return;
    }

    // Use the material if the mesh has one
    if (a_Mesh.m_Material)
    {

        if(a_Mesh.m_Material->m_MetalicRoughness->m_BaseColorTexture)
        {
            if (m_CurrentlyBoundShader != m_TextureShader)
            {
                UseShader(m_TextureShader);
            }

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, a_Mesh.m_Material->m_MetalicRoughness->m_BaseColorTexture->m_TextureHandle);
            m_CurrentlyBoundShader->SetUniformInt("uTexture", 0);

            auto& sampler = a_Mesh.m_Material->m_MetalicRoughness->m_BaseColorTexture->m_Sampler;
            UseSampler(sampler);
        }
        else
        {
            if (m_CurrentlyBoundShader != m_MeshShader)
            {
                UseShader(m_MeshShader);
            }
        }

        if(a_Mesh.m_Material->m_MetalicRoughness)
        {
            m_CurrentlyBoundShader->SetUniformVec4f("uBaseColorFactor", 1, &a_Mesh.m_Material->m_MetalicRoughness->m_BaseColorFactor);
        }

        SetCullingEnabled(!a_Mesh.m_Material->m_DoubleSided);
        
    }
    else
    {
        if (m_CurrentlyBoundShader != m_MeshShader)
        {
            UseShader(m_MeshShader);
        }
    }

    mat4 eye = m_CurrentCamera->GetView();
    mat4 projection = m_CurrentCamera->GetProjection();

    mat4 res = a_Transform * eye * projection;
    m_CurrentlyBoundShader->SetUniformMat4f("uTransform", 1, GL_FALSE, &res);


    glBindVertexArray(a_Mesh.m_VAO);
    if (a_Mesh.m_EBO != 0)
    {
        glDrawElements(GL_TRIANGLES, a_Mesh.m_VertexCount, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, a_Mesh.m_VertexCount);
    }
    glBindVertexArray(0);

    helpers::CheckForErrors();
}

void tabi::graphics::Renderer::UseCamera(const tabi::shared_ptr<Camera> a_Camera)
{
    m_CurrentCamera = a_Camera;
}

void Renderer::SetDrawMode(EDrawMode a_DrawMode)
{
    if (!m_Initialized)
    {
        tabi::logger::TabiError("Please initialize the renderer before trying to set the draw mode!");
        return;
    }

    unsigned int mode = 0;

    switch (a_DrawMode)
    {
    case EDrawMode::Line:
    {
        mode = GL_LINE;
        break;
    }
    case EDrawMode::Point:
    {
        mode = GL_POINT;
        break;
    }
    case EDrawMode::Fill:
    {
        mode = GL_FILL;
        break;
    }
    default:
    {
        break;
    }
    }

    glPolygonMode(GL_FRONT_AND_BACK, mode);

    helpers::CheckForErrors();
}

void tabi::graphics::Renderer::UseShader(tabi::shared_ptr<IShader> a_Shader)
{
    if (!m_Initialized)
    {
        tabi::logger::TabiError("Please initialize the renderer before trying to use a sampler!");
        return;
    }

    if (a_Shader == m_CurrentlyBoundShader)
    {
        return;
    }

    if (a_Shader)
    {
        if (a_Shader->UseShader())
        {
            m_CurrentlyBoundShader = a_Shader;
        }
    }
    else
    {
        UseShader(m_MeshShader);
    }
}

void Renderer::UseSampler(tabi::shared_ptr<ISampler> a_Sampler)
{
    if (!m_Initialized)
    {
        tabi::logger::TabiError("Please initialize the renderer before trying to use a sampler!");
        return;
    }

    if(a_Sampler == m_CurrentlyBoundSampler)
    {
        return;
    }

    if(a_Sampler)
    {
        if (a_Sampler->UseSampler())
        {
            m_CurrentlyBoundSampler = a_Sampler;
        }
    }
    else
    {
        UseSampler(m_TextureSampler);
    }
    
}

void tabi::graphics::Renderer::SetCullingEnabled(bool a_Enabled)
{
    if (!m_Initialized)
    {
        tabi::logger::TabiError("Please initialize the renderer before trying to enable or disable culling!");
        return;
    }

    if (a_Enabled == m_BackfaceCullingEnabled)
    {
        return;
    }

    if (a_Enabled)
    {
        glEnable(GL_CULL_FACE);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    m_BackfaceCullingEnabled = a_Enabled;
}

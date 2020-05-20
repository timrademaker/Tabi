#pragma once

#include "IRenderer.h"

namespace tabi
{
    namespace graphics
    {
        class Renderer : public IRenderer
        {
        public:
            Renderer() = default;
            virtual ~Renderer() override = default;

            virtual MeshHandle BufferMesh(Mesh& a_Mesh, const bool a_CleanUpMeshDataAfterBuffering = true, EBufferMode a_BufferMode = EBufferMode::Static) const override;
            virtual TextureHandle BufferTexture(const Texture& a_Texture, const EBufferMode a_BufferMode = EBufferMode::Static) const override;    // GL_TEXTURE_BUFFER
            virtual ShaderHandle CreateShaderProgram(const char* a_VertexShader, const int a_VertexShaderLength, const char* a_FragmentShader, const int a_FragmentShaderLength) const override;
            virtual ShaderHandle CreateShaderProgram(const char* a_VertexShaderPath, const char* a_FragmentShaderPath) const override;
        };
    }
}
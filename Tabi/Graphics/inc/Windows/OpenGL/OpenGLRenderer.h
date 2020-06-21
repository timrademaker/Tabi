#pragma once

#include "IRenderer.h"

namespace tabi
{
    class ISampler;
    namespace graphics
    {
        class Renderer : public IRenderer
        {
        public:
            Renderer();
            virtual ~Renderer() override = default;

            virtual void Initialize(tabi::shared_ptr<IWindow> a_Window) override;

            virtual bool BufferMesh(Mesh& a_Mesh, const bool a_CleanUpMeshDataAfterBuffering = true, EBufferMode a_BufferMode = EBufferMode::Static) const override;
            virtual bool BufferTexture(Texture& a_Texture, const bool a_CleanUpTextureDataAfterBuffering = true) const override;
            virtual ShaderHandle CreateShaderProgram(const char* a_VertexShader, const int a_VertexShaderLength, const char* a_FragmentShader, const int a_FragmentShaderLength) const override;
            virtual ShaderHandle CreateShaderProgram(const char* a_VertexShaderPath, const char* a_FragmentShaderPath) const override;

            virtual void UseShader(const ShaderHandle a_ShaderHandle) override;

            virtual void RenderMesh(const Mesh& a_Mesh, const mat4& a_Transform) override;

            virtual void UseCamera(const tabi::shared_ptr<Camera> a_Camera) override;

            virtual void SetDrawMode(EDrawMode a_DrawMode) override;

            void UseSampler(tabi::shared_ptr<ISampler> a_Sampler);
            void SetCullingEnabled(bool a_Enabled);

        private:
            bool m_Initialized = false;

            tabi::shared_ptr<ISampler> m_TextureSampler;
            ShaderHandle m_TextureShader;
            ShaderHandle m_MeshShader;

            ShaderHandle m_CurrentlyBoundShader;
            tabi::shared_ptr<ISampler> m_CurrentlyBoundSampler;
            bool m_BackfaceCullingEnabled = false;

            tabi::shared_ptr<Camera> m_CurrentCamera;
        };
    }
}
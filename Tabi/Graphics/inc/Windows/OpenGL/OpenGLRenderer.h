#pragma once

#include "IRenderer.h"

namespace tabi
{
    class ISampler;
    class IShader;

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


            virtual void RenderMesh(const Mesh& a_Mesh, const mat4& a_Transform) override;

            virtual void UseCamera(const tabi::shared_ptr<Camera> a_Camera) override;

            virtual void SetDrawMode(EDrawMode a_DrawMode) override;

            void UseShader(tabi::shared_ptr<IShader> a_Shader);
            void UseSampler(tabi::shared_ptr<ISampler> a_Sampler);
            void SetCullingEnabled(bool a_Enabled);

        private:
            tabi::shared_ptr<ISampler> m_TextureSampler;
            tabi::shared_ptr<IShader> m_TextureShader;
            tabi::shared_ptr<IShader> m_MeshShader;

            tabi::shared_ptr<IShader> m_CurrentlyBoundShader;
            tabi::shared_ptr<ISampler> m_CurrentlyBoundSampler;

            bool m_BackfaceCullingEnabled = false;

            tabi::shared_ptr<Camera> m_CurrentCamera;
        };
    }
}
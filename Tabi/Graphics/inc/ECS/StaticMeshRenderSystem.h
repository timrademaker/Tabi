#pragma once

#include <ISystem.h>

namespace tabi
{
    class StaticMeshRenderSystem final : public ISystem
    {
    public:
        StaticMeshRenderSystem(tabi::ComponentManager* a_ComponentManager);
        virtual ~StaticMeshRenderSystem() override;

        virtual void OnRender() override;

    private:
        void Setup();

    private:
        class Buffer* m_ConstantDataBuffer = nullptr;   // Data shared between all meshes
        class GraphicsPipeline* m_MeshInstancePipeline = nullptr;
    };
}

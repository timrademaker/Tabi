#pragma once

#include <ISystem.h>

namespace tabi
{
    class StaticMeshRenderSystem : public tabi::ISystem
    {
    public:
        StaticMeshRenderSystem(tabi::ComponentManager* a_ComponentManager)
            : ISystem(a_ComponentManager)
        {
        }

        virtual void OnUpdate(float a_DeltaTime) override;
    };

}
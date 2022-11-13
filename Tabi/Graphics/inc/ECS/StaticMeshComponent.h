#pragma once

#include <TabiPointers.h>

#include <Resources/Mesh.h>

namespace tabi
{
    struct StaticMeshComponent
    {
        ~StaticMeshComponent();

        bool m_IsVisible = true;

        tabi::shared_ptr<Mesh> m_Mesh = nullptr;

        /** Mesh data used for rendering */
        class Buffer* m_MeshConstants = nullptr;
    };
}

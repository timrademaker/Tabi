#pragma once

#include "Resources/Mesh.h"

#include <TabiPointers.h>
#include <Math/vec3.h>

namespace tabi
{
    struct StaticMeshComponent
    {
        tabi::shared_ptr<Mesh> m_Mesh;
        tabi::vec3 m_RelativeMeshRotation{ 0.0f, 0.0f, 0.0f };

        bool m_IsEnabled = true;
    };
}

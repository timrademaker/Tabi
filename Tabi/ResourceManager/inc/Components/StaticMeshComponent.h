#pragma once

#include "Resources/Mesh.h"

#include <TabiPointers.h>

namespace tabi
{
    struct StaticMeshComponent
    {
        tabi::shared_ptr<Mesh> m_Mesh;

        bool m_IsEnabled = true;
    };
}

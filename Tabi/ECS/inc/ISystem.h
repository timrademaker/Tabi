#pragma once

#include "ECS_Constants.h"

#include <TabiContainers.h>

namespace tabi
{
    using SystemSignature = bitset<MAX_COMPONENTS>;

    class ISystem
    {
    public:
        void OnUpdate(float a_DeltaTime);

    public:
        tabi::set<Entity> m_Entities;

        SystemSignature m_RequiredComponents;
    };
}

#pragma once

#include "ECS_Constants.h"

#include <TabiContainers.h>
#include "TabiMacros.h"

namespace tabi
{
    using SystemSignature = bitset<MAX_COMPONENTS>;

    class ISystem
    {
    public:
        virtual void OnUpdate(float a_DeltaTime) { TABI_UNUSED(a_DeltaTime); }

    public:
        tabi::set<Entity::ID_t> m_Entities;

        SystemSignature m_RequiredComponents;
    };
}

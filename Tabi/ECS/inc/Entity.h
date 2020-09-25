#pragma once

#include "ECS_Constants.h"

#include <TabiContainers.h>

namespace tabi
{
    class Entity
    {
    public:
        using ID_t = size_t;

        bool operator==(const Entity& a_Rhs) { return m_ID == a_Rhs.m_ID; }
        bool operator!=(const Entity& a_Rhs) { return !(m_ID == a_Rhs.m_ID); }

    public:
        ID_t m_ID;
    };
    
    /// The signature of an entity. Represents the components attached to the entity
    using EntitySignature = tabi::bitset<MAX_COMPONENTS>;
}

#pragma once

#include "ECS_Constants.h"

#include <TabiContainers.h>

namespace tabi
{
    class Entity
    {
    public:
        using ID_t = size_t;

    public:
        ID_t m_ID;
    };
    
    using EntitySignature = tabi::bitset<MAX_COMPONENTS>;
}

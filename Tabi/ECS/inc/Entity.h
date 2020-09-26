#pragma once

#include "ECS_Constants.h"

#include <TabiContainers.h>

namespace tabi
{
    using Entity = size_t;
    
    /// The signature of an entity. Represents the components attached to the entity
    using EntitySignature = tabi::bitset<MAX_COMPONENTS>;
}

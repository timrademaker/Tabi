#pragma once

#include "Entity.h"

namespace tabi
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;

        virtual void OnEntityDestroyed(const Entity::ID_t a_EntityID) = 0;
    };
}

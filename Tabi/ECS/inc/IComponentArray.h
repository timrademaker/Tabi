#pragma once

#include "Entity.h"

namespace tabi
{
    class IComponentArray
    {
    public:
        IComponentArray() = default;
        IComponentArray(IComponentArray&) = delete;
        IComponentArray(const IComponentArray&) = delete;
        virtual ~IComponentArray() = default;

        /**
        * @brief Called when an entity is destroyed, so that it can be removed from the component array
        */
        virtual void OnEntityDestroyed(const Entity::ID_t a_EntityID) = 0;
    };
}

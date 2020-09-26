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
         * @params a_Entity The entity that was destroyed
         */
        virtual void OnEntityDestroyed(const Entity a_Entity) = 0;
    };
}

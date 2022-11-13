#pragma once

#include "ECS_Constants.h"
#include "Entity.h"

#include <TabiContainers.h>

namespace tabi
{
    class ComponentManager;

    class ISystem
    {
    public:
        ISystem(tabi::ComponentManager* a_ComponentManager) 
            : m_ComponentManager(a_ComponentManager) {}
        ISystem(ISystem&) = delete;
        ISystem(const ISystem&) = delete;
        virtual ~ISystem() = default;

        /**
         * @brief Updates a system
         * @param a_DeltaTime The time between the previous update and this update
         */
        virtual void OnUpdate(float a_DeltaTime) { }
        /**
         * @brief Function that is called after all systems have been updated and a new frame has started
         */
        virtual void OnRender() { }

    public:
        /// The entities that have the components this system requires
        tabi::set<Entity> m_Entities;
        /// Non-owning pointer to the component manager (used to retrieve components)
        ComponentManager* m_ComponentManager;
    };
}

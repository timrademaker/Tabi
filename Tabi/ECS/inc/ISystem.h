#pragma once

#include "ECS_Constants.h"
#include "Entity.h"

#include <TabiContainers.h>
#include "TabiMacros.h"

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
        * @params a_DeltaTime The time between this update and the last update
        */
        virtual void OnUpdate(float a_DeltaTime) { TABI_UNUSED(a_DeltaTime); }

    public:
        /// The entities that have the components this system requires
        tabi::set<Entity::ID_t> m_Entities;
        /// Non-owning pointer to the component manager (used to retrieve components)
        ComponentManager* m_ComponentManager;
    };
}

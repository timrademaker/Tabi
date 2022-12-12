#pragma once

#include "ECS_Constants.h"
#include "Entity.h"
#include "ComponentManager.h"

#include <TabiContainers.h>

namespace tabi
{
    using SystemSignature = bitset<MAX_COMPONENTS>;

    class ISystem
    {
    public:
        ISystem(tabi::ComponentManager* a_ComponentManager) 
            : m_ComponentManager(a_ComponentManager) {}
        ISystem(ISystem&) = delete;
        ISystem(const ISystem&) = delete;
        virtual ~ISystem() = 0;

        SystemSignature GetSystemSignature() const { return m_Signature; }

        /**
         * @brief Adds an entity to the system, signaling that it contains the components required by this system
         * @param a_Entity The entity to add
         */
        void AddEntity(Entity a_Entity)
        {
            m_Entities.insert(a_Entity);
        }
        /**
         * @brief Removes an entity from the system, signaling that it either no contains the components required by this system, or that it was destroyed
         * @param a_Entity The entity to remove
         */
        void RemoveEntity(Entity a_Entity)
        {
            m_Entities.erase(a_Entity);
        }

        /**
         * @brief Updates a system
         * @param a_DeltaTime The time between the previous update and this update
         */
        virtual void OnUpdate(float a_DeltaTime) { TABI_UNUSED(a_DeltaTime); }
        /**
         * @brief Function that is called after all systems have been updated and a new frame has started
         */
        virtual void OnRender() { }

    protected:
        /**
         * @brief Set a component type as required for this system
         * @note Should not be called after the system has been registered to the system manager
         */
        template<typename ComponentType>
        void RequireComponent()
        {
            TABI_ASSERT(m_ComponentManager != nullptr);

            m_Signature.set(m_ComponentManager->GetComponentTypeID<ComponentType>());
        }

    protected:
        /** The entities that have the components this system requires */
        tabi::set<Entity> m_Entities;
        /** Non-owning pointer to the component manager (used to retrieve components) */
        ComponentManager* m_ComponentManager;

    private:
        /** The required components for this system */
        SystemSignature m_Signature{};
    };

    inline ISystem::~ISystem() = default;
}

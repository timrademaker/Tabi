#pragma once

#include "IComponentArray.h"
#include "ComponentArray.h"

#include <TabiContainers.h>
#include <TabiPointers.h>
#include <TabiMacros.h>

#include <Logging.h>

#include <cstdint>

namespace tabi
{
    using ComponentTypeID = std::uint8_t;

    class ComponentManager
    {
        using ComponentTypeHash = const char*;

    public:
        /**
         * @brief Register a component type so that it can be used
         * @tparam ComponentType The component type to register
         * @tparam MaxComponentsOfType The maximum number of components of ComponentType that can be created at a time
         */
        template<typename ComponentType, size_t MaxComponentsOfType = MAX_ENTITIES>
        void RegisterComponentType();

        /**
         * @brief Gets the ID of a component type
         * @returns The ID of a component type
         */
        template<typename ComponentType>
        ComponentTypeID GetComponentTypeID();

        /**
         * @brief Add a component to an entity
         * @param a_Entity The entity to add the component to
         * @param a_Component The component to add to the entity
         */
        template<typename ComponentType>
        void AddComponent(Entity a_Entity, ComponentType& a_Component);

        /**
         * @brief Get a component that is attached to an entity
         * @param a_Entity The entity to get the component from
         */
        template<typename ComponentType>
        ComponentType& GetComponent(Entity a_Entity);

        /**
         * @brief Remove a component from an entity
         * @param a_Entity The entity to remove the component from
         */
        template<typename ComponentType>
        void RemoveComponent(Entity a_Entity);

        /**
         * @brief Called when an entity is destroyed
         * @param a_Entity The entity that was destroyed
         */
        void OnEntityDestroyed(Entity a_Entity) const;

    private:
        /**
         * @brief Hashes a component type. The hash can be used as a key in a map
         * @returns A hash of the component type
         */
        template<typename ComponentType>
        static ComponentTypeHash HashComponentType();

        /**
         * @brief Helper function to get the component array of a certain component type
         * @returns The component array
         */
        template<typename ComponentType>
        tabi::shared_ptr<ComponentArray<ComponentType>> GetComponentArray();

    private:
        /// A map containing component type IDs belonging to component types
        tabi::map<ComponentTypeHash, ComponentTypeID> m_ComponentTypes;
        /// A map containing component arrays
        tabi::map<ComponentTypeHash, tabi::shared_ptr<IComponentArray>> m_ComponentArrays;

        /// The next available ID for new component types
        ComponentTypeID m_NextComponentType = 0;
    };

    template<typename ComponentType, size_t MaxComponentsOfType>
    inline void ComponentManager::RegisterComponentType()
    {
        auto hash = HashComponentType<ComponentType>();
        
        // Make sure the component type has not already been registered
        TABI_ASSERT(m_ComponentTypes.find(hash) == m_ComponentTypes.end());

        m_ComponentTypes.insert(tabi::make_pair(hash, m_NextComponentType));
        m_ComponentArrays.insert(tabi::make_pair(hash, tabi::make_shared<ComponentArray<ComponentType>>(MaxComponentsOfType)));

        ++m_NextComponentType;
    }

    template<typename ComponentType>
    inline ComponentTypeID ComponentManager::GetComponentTypeID()
    {
        auto hash = HashComponentType<ComponentType>();
        
        // Make sure the component type has been registered
        if (m_ComponentTypes.find(hash) == m_ComponentTypes.end())
        {
            TABI_WARN("Trying to get a component type ID from a component type that has not yet been registered. Registering component type.");
            RegisterComponentType<ComponentType>();
        }

        return m_ComponentTypes[hash];
    }

    template<typename ComponentType>
    inline void ComponentManager::AddComponent(const Entity a_Entity, ComponentType& a_Component)
    {
        GetComponentArray<ComponentType>()->AddComponent(a_Entity, a_Component);
    }

    template<typename ComponentType>
    inline ComponentType& ComponentManager::GetComponent(const Entity a_Entity)
    {
        return GetComponentArray<ComponentType>()->GetComponent(a_Entity);
    }

    template<typename ComponentType>
    inline void ComponentManager::RemoveComponent(Entity a_Entity)
    {
        GetComponentArray<ComponentType>()->RemoveComponent(a_Entity);
    }

    template<typename ComponentType>
    inline ComponentManager::ComponentTypeHash ComponentManager::HashComponentType()
    {
        return typeid(ComponentType).name();
    }

    template<typename ComponentType>
    inline tabi::shared_ptr<ComponentArray<ComponentType>> ComponentManager::GetComponentArray()
    {
        auto hash = HashComponentType<ComponentType>();

        // Make sure the component type has been registered
        if (m_ComponentTypes.find(hash) == m_ComponentTypes.end())
        {
            TABI_WARN("Trying to get a component type ID from a component type that has not yet been registered. Registering component type.");
            RegisterComponentType<ComponentType>();
        }

        return tabi::static_pointer_cast<ComponentArray<ComponentType>>(m_ComponentArrays[hash]);
    }
}

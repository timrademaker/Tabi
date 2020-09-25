#pragma once

#include "IComponentArray.h"
#include "ComponentArray.h"

#include <TabiContainers.h>
#include <TabiPointers.h>

#include <cstdint>

namespace tabi
{
    class Entity;

    using ComponentTypeID = std::uint8_t;

    class ComponentManager
    {
        using ComponentTypeHash = const char*;

    public:
        /**
        * @brief Register a component type so that it can be used
        */
        template<typename ComponentType>
        void RegisterComponentType();

        /**
        * @brief Gets the ID of a component type
        * @returns The ID of a component type
        */
        template<typename ComponentType>
        ComponentTypeID GetComponentTypeID();

        /**
        * @brief Add a component to an entity
        * @params a_EntityID The ID of the entity to add the component to
        * @params a_Component The component to add to the entity
        */
        template<typename ComponentType>
        void AddComponent(const Entity::ID_t a_EntityID, ComponentType& a_Component);

        /**
        * @brief Get a component that is attached to an entity
        * @params a_EntityID The ID of the entity to get the component from
        */
        template<typename ComponentType>
        ComponentType& GetComponent(const Entity::ID_t a_EntityID);

        /**
        * @brief Remove a component from an entity
        * @params a_EntityID The ID of the entity to remove the component from
        */
        template<typename ComponentType>
        void RemoveComponent(Entity::ID_t a_EntityID);

        /**
        * @brief Called when an entity is destroyed
        * @params a_EntityID The ID of the entity that was destroyed
        */
        void OnEntityDestroyed(const Entity::ID_t a_EntityID);

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

    template<typename ComponentType>
    inline void ComponentManager::RegisterComponentType()
    {
        auto hash = HashComponentType<ComponentType>();
        
        // Make sure the component type has not already been registered
        assert(m_ComponentTypes.find(hash) == m_ComponentTypes.end());

        m_ComponentTypes.insert(tabi::make_pair(hash, m_NextComponentType));
        m_ComponentArrays.insert(tabi::make_pair(hash, tabi::make_shared<ComponentArray<ComponentType>>()));

        ++m_NextComponentType;
    }

    template<typename ComponentType>
    inline ComponentTypeID ComponentManager::GetComponentTypeID()
    {
        auto hash = HashComponentType<ComponentType>();
        
        // Make sure the component type has been registered
        if (m_ComponentTypes.find(hash) == m_ComponentTypes.end())
        {
            RegisterComponentType<ComponentType>();
        }

        return m_ComponentTypes[hash];
    }

    template<typename ComponentType>
    inline void ComponentManager::AddComponent(const Entity::ID_t a_EntityID, ComponentType& a_Component)
    {
        GetComponentArray<ComponentType>()->AddComponent(a_EntityID, a_Component);
    }

    template<typename ComponentType>
    inline ComponentType& ComponentManager::GetComponent(const Entity::ID_t a_EntityID)
    {
        return GetComponentArray<ComponentType>()->GetComponent(a_EntityID);
    }

    template<typename ComponentType>
    inline void ComponentManager::RemoveComponent(Entity::ID_t a_EntityID)
    {
        GetComponentArray<ComponentType>()->RemoveComponent(a_EntityID);
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
            RegisterComponentType<ComponentType>();
        }

        return tabi::static_pointer_cast<ComponentArray<ComponentType>>(m_ComponentArrays[hash]);
    }
}

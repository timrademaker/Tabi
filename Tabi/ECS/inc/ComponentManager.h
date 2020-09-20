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
        template<typename ComponentType>
        void RegisterComponentType();

        template<typename ComponentType>
        ComponentTypeID GetComponentType();

        template<typename ComponentType>
        void AddComponent(const Entity::ID_t a_EntityID, ComponentType& a_Component);

        template<typename ComponentType>
        ComponentType& GetComponent(const Entity::ID_t a_EntityID);

        template<typename ComponentType>
        void RemoveComponent(Entity::ID_t a_EntityID);

        void OnEntityDestroyed(const Entity::ID_t a_EntityID);

        template<typename ComponentType>
        static ComponentTypeHash HashComponentType();

    private:
        template<typename ComponentType>
        tabi::shared_ptr<ComponentArray<ComponentType>> GetComponentArray();

    private:
        tabi::map<ComponentTypeHash, ComponentTypeID> m_ComponentTypes;
        tabi::map<ComponentTypeHash, tabi::shared_ptr<IComponentArray>> m_ComponentArrays;

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
    inline ComponentTypeID ComponentManager::GetComponentType()
    {
        auto hash = HashComponentType<ComponentType>();
        
        // Make sure the component type has been registered
        assert(m_ComponentTypes.find(hash) != m_ComponentTypes.end());

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

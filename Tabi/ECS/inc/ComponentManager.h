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
        void AddComponent(const Entity& a_Entity, ComponentType& a_Component);

        template<typename ComponentType>
        ComponentType& GetComponent(const Entity& a_Entity);

        template<typename ComponentType>
        void RemoveComponent(Entity& a_Entity);

        void OnEntityDestroyed(const Entity& a_Entity);

    private:
        template<typename ComponentType>
        ComponentTypeHash HashComponentType();

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
        m_ComponentArrays.insert(tabi::make_pair(hash, tabi::make_shared <ComponentArray<ComponentType>()));

        ++m_NextComponentType;
    }

    template<typename ComponentType>
    inline ComponentTypeID ComponentManager::GetComponentType()
    {
        auto hash = HashComponentType<ComponentType>();
        
        // Make sure the component type has been registered
        assert(m_ComponentTypes.find(hash) != m_ComponentTypes.end());

        return m_ComponentArrays[hash];
    }

    template<typename ComponentType>
    inline void ComponentManager::AddComponent(const Entity& a_Entity, ComponentType& a_Component)
    {
        GetComponentArray<ComponentType>()->AddComponent(a_Entity, a_Component);
    }

    template<typename ComponentType>
    inline ComponentType& ComponentManager::GetComponent(const Entity& a_Entity)
    {
        return GetComponentArray<ComponentType>()->GetComponent(a_Entity);
    }

    template<typename ComponentType>
    inline void ComponentManager::RemoveComponent(Entity& a_Entity)
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
        assert(m_ComponentTypes.find(hash) != m_ComponentTypes.end());

        return tabi::static_pointer_cast<ComponentArray<ComponentType>>(m_ComponentArrays[hash]);
    }
}

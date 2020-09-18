#pragma once

#include "IComponentArray.h"

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
        void AddComponent(const Entity& a_Entity, ComponentType a_Component);

        template<typename ComponentType>
        ComponentType& GetComponent(const Entity& a_Entity);

        template<typename ComponentType>
        void RemoveComponent(Entity& a_Entity);

        void OnEntityDestroyed(const Entity& a_Entity);

    private:
        tabi::map<ComponentTypeHash, ComponentTypeID> m_ComponentTypes;
        tabi::map<ComponentTypeHash, tabi::shared_ptr<IComponentArray>> m_ComponentArrays;

    };

}
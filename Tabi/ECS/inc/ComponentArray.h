#pragma once

#include "IComponentArray.h"
#include "ECS_Constants.h"
#include "Entity.h"

#include <TabiContainers.h>
#include <TabiMacros.h>


namespace tabi
{
    template<typename ComponentType>
    class ComponentArray : public IComponentArray
    {
    public:
        ComponentArray() = default;
        ComponentArray(ComponentArray&) = delete;
        ComponentArray(const ComponentArray&) = delete;
        virtual ~ComponentArray() override = default;

        /**
         * @brief Add a component to an entity
         * @params a_Entity The entity to add the component to
         * @params a_Component The component to add to the entity
         */
        void AddComponent(const Entity a_Entity, ComponentType& a_Component);
        /**
         * @brief Get a component from an entity
         * @params a_Entity The entity to retrieve the component from
         * @returns A reference to the component attached to the entity. The reference might be invalidated whenever a component of this type is removed
         */
        ComponentType& GetComponent(const Entity a_Entity);
        /** Remove a component from an entity. This operation can invalidate references to retrieved entities.
         * @brief Remove a component from an entity
         * @params a_Entity The entity to remove the component from
         */
        void RemoveComponent(const Entity a_Entity);
        
        virtual void OnEntityDestroyed(const Entity a_Entity) override;

    private:
        tabi::array<ComponentType, MAX_ENTITIES> m_Components;
        tabi::set<Entity> m_EntitiesWithComponent;
    };

    template <typename ComponentType>
    void ComponentArray<ComponentType>::AddComponent(const Entity a_Entity, ComponentType& a_Component)
    {
        // Check if the entity already has this component
        TABI_ASSERT(m_EntitiesWithComponent.find(a_Entity) == m_EntitiesWithComponent.end());

        m_Components[a_Entity] = a_Component;
        m_EntitiesWithComponent.insert(a_Entity);
    }

    template <typename ComponentType>
    ComponentType& ComponentArray<ComponentType>::GetComponent(const Entity a_Entity)
    {
        // Check if the entity has this component
        TABI_ASSERT(m_EntitiesWithComponent.find(a_Entity) != m_EntitiesWithComponent.end());

        return m_Components[a_Entity];
    }

    template <typename ComponentType>
    void ComponentArray<ComponentType>::RemoveComponent(const Entity a_Entity)
    {
        // Check if the entity has this component
        TABI_ASSERT(m_EntitiesWithComponent.find(a_Entity) != m_EntitiesWithComponent.end());

        // Zero out memory
        std::memset(&m_Components[a_Entity], 0, sizeof(ComponentType));      
        m_EntitiesWithComponent.erase(a_Entity);
    }

    template <typename ComponentType>
    void ComponentArray<ComponentType>::OnEntityDestroyed(const Entity a_Entity)
    {
        if(m_EntitiesWithComponent.find(a_Entity) != m_EntitiesWithComponent.end())
        {
            RemoveComponent(a_Entity);
        }
    }
}

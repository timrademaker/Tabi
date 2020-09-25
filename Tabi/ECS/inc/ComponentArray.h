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
        * @params a_EntityID The ID of the entity to add the component to
        * @params a_Component The component to add to the entity
        */
        void AddComponent(const Entity::ID_t a_EntityID, ComponentType& a_Component);
        /**
        * @brief Get a component from an entity
        * @params a_EntityID The ID of the entity to retrieve the component from
        * @returns A reference to the component attached to the entity. The reference might be invalidated whenever a component of this type is removed
        */
        ComponentType& GetComponent(const Entity::ID_t a_EntityID);
        /** Remove a component from an entity. This operation can invalidate references to retrieved entities.
        * @brief Remove a component from an entity
        * @params a_EntityID The ID of the entity to remove the component from
        */
        void RemoveComponent(const Entity::ID_t a_EntityID);

        virtual void OnEntityDestroyed(const Entity::ID_t a_EntityID) override;

    private:
        tabi::array<ComponentType, MAX_ENTITIES> m_Components;
        tabi::set<Entity::ID_t> m_EntitiesWithComponent;
    };

    template <typename ComponentType>
    void ComponentArray<ComponentType>::AddComponent(const Entity::ID_t a_EntityID, ComponentType& a_Component)
    {
        // Check if the entity alrady has this component
        TABI_ASSERT(m_EntitiesWithComponent.find(a_EntityID) == m_EntitiesWithComponent.end());

        m_Components[a_EntityID] = a_Component;
        m_EntitiesWithComponent.insert(a_EntityID);
    }

    template <typename ComponentType>
    ComponentType& ComponentArray<ComponentType>::GetComponent(const Entity::ID_t a_EntityID)
    {
        // Check if the entity has this component
        TABI_ASSERT(m_EntitiesWithComponent.find(a_EntityID) != m_EntitiesWithComponent.end());

        return m_Components[a_EntityID];
    }

    template <typename ComponentType>
    void ComponentArray<ComponentType>::RemoveComponent(const Entity::ID_t a_EntityID)
    {
        // Check if the entity has this component
        TABI_ASSERT(m_EntitiesWithComponent.find(a_EntityID) != m_EntitiesWithComponent.end());

        // Zero out memory
        std::memset(&m_Components[a_EntityID], 0, sizeof(ComponentType));      
        m_EntitiesWithComponent.erase(a_EntityID);
    }

    template <typename ComponentType>
    void ComponentArray<ComponentType>::OnEntityDestroyed(const Entity::ID_t a_EntityID)
    {
        if(m_EntitiesWithComponent.find(a_EntityID) != m_EntitiesWithComponent.end())
        {
            RemoveComponent(a_EntityID);
        }
    }
}

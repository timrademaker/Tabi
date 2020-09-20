#pragma once

#include "IComponentArray.h"
#include "ECS_Constants.h"
#include "Entity.h"

#include <TabiContainers.h>

#include <cassert>

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
        tabi::map<Entity::ID_t, size_t> m_EntityToIndex;
        tabi::map<size_t, Entity::ID_t> m_IndexToEntity;
        tabi::array<ComponentType, MAX_ENTITIES> m_Components;

        size_t m_NextComponentIndex = 0;
    };

    template <typename ComponentType>
    void ComponentArray<ComponentType>::AddComponent(const Entity::ID_t a_EntityID, ComponentType& a_Component)
    {
        // Check if the entity already has this component
        assert(m_EntityToIndex.find(a_EntityID) == m_EntityToIndex.end());

        size_t assignedIndex = m_NextComponentIndex;
        m_Components[assignedIndex] = a_Component;

        m_EntityToIndex[a_EntityID] = assignedIndex;
        m_IndexToEntity[assignedIndex] = a_EntityID;

        ++m_NextComponentIndex;
    }

    template <typename ComponentType>
    ComponentType& ComponentArray<ComponentType>::GetComponent(const Entity::ID_t a_EntityID)
    {
        // Check if the entity has this component
        assert(m_EntityToIndex.find(a_EntityID) != m_EntityToIndex.end());

        return m_Components[m_EntityToIndex[a_EntityID]];
    }

    template <typename ComponentType>
    void ComponentArray<ComponentType>::RemoveComponent(const Entity::ID_t a_EntityID)
    {
        // Check if the entity has this component
        assert(m_EntityToIndex.find(a_EntityID) != m_EntityToIndex.end());

        // Find index in array
        size_t componentIndex = m_EntityToIndex[a_EntityID];
        size_t lastComponentIndex = m_NextComponentIndex - 1;

        // Move the last component to the component that is being removed
        m_Components[componentIndex] = m_Components[lastComponentIndex];
        size_t lastComponentOwner = m_IndexToEntity[lastComponentIndex];
        m_EntityToIndex[lastComponentOwner] = componentIndex;
        m_IndexToEntity[componentIndex] = lastComponentIndex;

        // Remove entity from maps
        m_EntityToIndex.erase(a_EntityID);
        m_IndexToEntity.erase(lastComponentIndex);

        --m_NextComponentIndex;
    }

    template <typename ComponentType>
    void ComponentArray<ComponentType>::OnEntityDestroyed(const Entity::ID_t a_EntityID)
    {
        if(m_EntityToIndex.find(a_EntityID) != m_EntityToIndex.end())
        {
            RemoveComponent(a_EntityID);
        }
    }
}

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
        virtual ~ComponentArray() override = default;

        void AddComponent(const Entity& a_Entity, ComponentType& a_Component);
        ComponentType& GetComponent(const Entity& a_Entity);
        void RemoveComponent(const Entity& a_Entity);

        virtual void OnEntityDestroyed(const Entity& a_Entity) override;

    private:
        tabi::map<Entity::ID_t, size_t> m_EntityToIndex;
        tabi::map<size_t, Entity::ID_t> m_IndexToEntity;
        tabi::array<ComponentType, MAX_COMPONENTS> m_Components;

        size_t m_NextComponentIndex = 0;
    };

    template <typename ComponentType>
    void ComponentArray<ComponentType>::AddComponent(const Entity& a_Entity, ComponentType& a_Component)
    {
        // Check if the entity already has this component
        assert(m_EntityToIndex.find(a_Entity.m_ID) == m_EntityToIndex.end());

        size_t assignedIndex = m_NextComponentIndex;
        m_Components[assignedIndex] = std::move(a_Component);

        m_EntityToIndex[a_Entity.m_ID] = assignedIndex;
        m_IndexToEntity[assignedIndex] = a_Entity.m_ID;

        ++m_NextComponentIndex;
    }

    template <typename ComponentType>
    ComponentType& ComponentArray<ComponentType>::GetComponent(const Entity& a_Entity)
    {
        // Check if the entity has this component
        assert(m_EntityToIndex.find(a_Entity.m_ID) != m_EntityToIndex.end());

        return m_Components[m_EntityToIndex[a_Entity.m_ID]];
    }

    template <typename ComponentType>
    void ComponentArray<ComponentType>::RemoveComponent(const Entity& a_Entity)
    {
        // Check if the entity has this component
        assert(m_EntityToIndex.find(a_Entity.m_ID) != m_EntityToIndex.end());

        // Find index in array
        size_t componentIndex = m_EntityToIndex[a_Entity.m_ID];
        size_t lastComponentIndex = m_NextComponentIndex - 1;

        // Switch last array element with the component
        m_Components[componentIndex] = m_Components[lastComponentIndex];
        size_t lastComponentOwner = m_IndexToEntity[lastComponentIndex];
        m_EntityToIndex[lastComponentIndex] = componentIndex;

        // Remove entity from maps
        m_EntityToIndex.erase(a_Entity.m_ID);
        m_IndexToEntity.erase(lastComponentIndex);

        --m_NextComponentIndex;
    }

    template <typename ComponentType>
    void ComponentArray<ComponentType>::OnEntityDestroyed(const Entity& a_Entity)
    {
        if(m_EntityToIndex.find(a_Entity.m_ID) != m_EntityToIndex.end())
        {
            RemoveComponent(a_Entity);
        }
    }
}

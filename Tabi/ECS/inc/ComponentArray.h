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
        ComponentArray(const size_t a_MaxComponentsOfType = MAX_COMPONENTS)
        {
            m_Components.resize(a_MaxComponentsOfType);

            for (size_t i = 0; i < a_MaxComponentsOfType; ++i)
            {
                m_AvailableComponentIndices.push(i);
            }
        }

        TABI_NO_MOVE(ComponentArray);
        TABI_NO_COPY(ComponentArray);
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
        tabi::vector<ComponentType> m_Components;
        tabi::queue<size_t> m_AvailableComponentIndices;

        tabi::unordered_map<Entity, size_t> m_EntityToComponentIndex;
    };

    template<typename ComponentType>
    void ComponentArray<ComponentType>::AddComponent(const Entity a_Entity, ComponentType& a_Component)
    {
        TABI_ASSERT(m_EntityToComponentIndex.find(a_Entity) == m_EntityToComponentIndex.end(), "Entity already has a component of this type");
        TABI_ASSERT(!m_AvailableComponentIndices.empty(), "Trying to add more components of this type than expected");


        auto index = m_AvailableComponentIndices.front();
        m_AvailableComponentIndices.pop();
        m_Components[index] = a_Component;
        m_EntityToComponentIndex.insert({ a_Entity, index });
    }

    template<typename ComponentType>
    ComponentType& ComponentArray<ComponentType>::GetComponent(const Entity a_Entity)
    {
        TABI_ASSERT(m_EntityToComponentIndex.find(a_Entity) != m_EntityToComponentIndex.end(), "Entity does not have a component of this type");

        return m_Components[m_EntityToComponentIndex[a_Entity]];
    }

    template<typename ComponentType>
    void ComponentArray<ComponentType>::RemoveComponent(const Entity a_Entity)
    {
        TABI_ASSERT(m_EntityToComponentIndex.find(a_Entity) != m_EntityToComponentIndex.end(), "Entity does not have a component of this type");

        // Zero out memory
        std::memset(&m_Components[m_EntityToComponentIndex[a_Entity]], 0, sizeof(ComponentType));
        m_EntityToComponentIndex.erase(a_Entity);
        m_AvailableComponentIndices.push(m_EntityToComponentIndex[a_Entity]);
    }

    template<typename ComponentType>
    void ComponentArray<ComponentType>::OnEntityDestroyed(const Entity a_Entity)
    {
        if(m_EntityToComponentIndex.find(a_Entity) != m_EntityToComponentIndex.end())
        {
            RemoveComponent(a_Entity);
        }
    }
}

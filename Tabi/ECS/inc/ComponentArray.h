#pragma once

#include "IComponentArray.h"
#include "ECS_Constants.h"

#include <TabiContainers.h>

namespace tabi
{
    template<typename ComponentType>
    class ComponentArray : public IComponentArray
    {
    public:
        ComponentArray();
        ~ComponentArray();

        void CreateComponent(const Entity& a_Entity, ComponentType a_Component);
        virtual void OnEntityDestroyed(const Entity& a_Entity) override;

    private:
        tabi::map<Entity::ID_t, size_t> m_EntityToIndex;
        tabi::map<size_t, Entity::ID_t> m_IndexToEntity;
        tabi::array<ComponentType, MAX_COMPONENTS> m_Components;

    };
}
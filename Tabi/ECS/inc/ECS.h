#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "ISystem.h"

#include <TabiPointers.h>

namespace tabi
{
    class ECS
    {
    public:
        ECS();
        ECS(const ECS&) = delete;
        ECS(ECS&) = delete;
        
        ~ECS() = default;

        /** EntityManager **/

        /**
         * @brief Create an entity
         * @returns The created entity
         */
        Entity CreateEntity();
        /**
         * @brief Destroy an entity and invalidates it
         * @param a_Entity The entity to destroy
         */
        void DestroyEntity(Entity& a_Entity);
        /**
         * @brief Get the signature of an entity (containing information about the components it has)
         * @param a_Entity The entity for which to retrieve the signature
         * @returns The signature of the entity
         */
        const EntitySignature& GetEntitySignature(const Entity a_Entity) const;

        /**  ComponentManager **/

        /**
         * @brief Add a component to an entity
         * @param a_Entity The entity to add the component to
         * @param a_Component The component to add to the entity
         */
        template<typename ComponentType>
        void AddComponent(const Entity a_Entity, ComponentType a_Component);
        /**
         * @brief Get a component that is attached to an entity
         * @param a_Entity The entity to get the component from
         */
        template<typename ComponentType>
        ComponentType& GetComponent(const Entity a_Entity);
        /**
         * @brief Remove a component from an entity
         * @param a_Entity The entity to remove the component from
         */
        template<typename ComponentType>
        void RemoveComponent(Entity a_Entity);
        /**
         * @brief Gets the ID of a component type
         * @returns The ID of a component type
         */
        template<typename ComponentType>
        ComponentTypeID GetComponentTypeID() const;
        /**
         * @brief Register a component type
         * @tparam ComponentType The component type to register
         * @tparam MaxComponentsOfType The maximum number of components of ComponentType that can be created at a time
         */
        template<typename ComponentType, size_t MaxComponentsOfType = MAX_ENTITIES>
        void RegisterComponentType();


        /** SystemManager **/

        /**
         * @brief Register a new system
         * @returns The created system
         */
        template<typename SystemType>
        std::enable_if_t<std::is_base_of_v<ISystem, SystemType>, tabi::shared_ptr<SystemType>> RegisterSystem();
        
        /**
         * @brief Updates all registered systems
         * @param a_DeltaTime The time between the previous update and this update
         */
        void Update(float a_DeltaTime) const;
        /**
         * @brief Calls OnRender() on all registered systems
         */
        void Render() const;

    private:
        tabi::unique_ptr<EntityManager> m_EntityManager;
        tabi::unique_ptr<ComponentManager> m_ComponentManager;
        tabi::unique_ptr<SystemManager> m_SystemManager;
    };

    template<typename ComponentType>
    inline void ECS::AddComponent(const Entity a_Entity, ComponentType a_Component)
    {
        m_ComponentManager->AddComponent(a_Entity, a_Component);
        
        auto sig = m_EntityManager->GetSignature(a_Entity);
        sig.set(m_ComponentManager->GetComponentTypeID<ComponentType>());
        m_EntityManager->SetSignature(a_Entity, sig);
        
        m_SystemManager->OnEntitySignatureChanged(a_Entity, sig);
    }

    template<typename ComponentType>
    inline ComponentType& ECS::GetComponent(const Entity a_Entity)
    {
        return m_ComponentManager->GetComponent<ComponentType>(a_Entity);
    }

    template<typename ComponentType>
    inline ComponentTypeID ECS::GetComponentTypeID() const
    {
        return m_ComponentManager->GetComponentTypeID<ComponentType>();
    }

    template <typename ComponentType, size_t MaxComponentsOfType>
    void ECS::RegisterComponentType()
    {
        m_ComponentManager->RegisterComponentType<ComponentType, MaxComponentsOfType>();
    }

    template<typename ComponentType>
    inline void ECS::RemoveComponent(Entity a_Entity)
    {
        m_ComponentManager->RemoveComponent<ComponentType>(a_Entity);
        
        auto sig = m_EntityManager->GetSignature(a_Entity);
        sig.set(m_ComponentManager->GetComponentTypeID<ComponentType>(), false);
        m_EntityManager->SetSignature(a_Entity, sig);

        m_SystemManager->OnEntitySignatureChanged(a_Entity, sig);
    }

    template<typename SystemType>
    std::enable_if_t<std::is_base_of_v<ISystem, SystemType>, tabi::shared_ptr<SystemType>> ECS::RegisterSystem()
    {
        auto system = m_SystemManager->RegisterSystem<SystemType>(m_ComponentManager.get());
        const auto signature = system->GetSystemSignature();

        // Add all existing entities with a matching signature to the system
        const auto& entitySignatures = m_EntityManager->GetAllSignatures();
        for (tabi::Entity ent = 0; ent < entitySignatures.size(); ++ent)
        {
            if ((entitySignatures[ent] & signature) == signature)
            {
                system->AddEntity(ent);
            }
            else
            {
                system->RemoveEntity(ent);
            }
        }

        return std::move(system);
    }
}

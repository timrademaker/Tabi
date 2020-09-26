#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

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
         * @params a_Entity The entity to destroy
         */
        void DestroyEntity(Entity& a_Entity);
        /**
         * @brief Get the signature of an entity (containing information about the components it has)
         * @params a_Entity The entity for which to retrieve the signature
         * @returns The signature of the entity
         */
        EntitySignature GetEntitySignature(const Entity a_Entity);
        /**
         * @brief Sets the signature of an entity
         * @params a_Entity The entity of which the signature should be modified
         * @params a_Signature The signature to apply to the entity
         */
        void SetEntitySignature(const Entity a_Entity, const EntitySignature& a_Signature);


        /**  ComponentManager **/

        /**
         * @brief Add a component to an entity
         * @params a_Entity The entity to add the component to
         * @params a_Component The component to add to the entity
         */
        template<typename ComponentType>
        void AddComponent(const Entity a_Entity, ComponentType a_Component);
        /**
         * @brief Get a component that is attached to an entity
         * @params a_Entity The entity to get the component from
         */
        template<typename ComponentType>
        ComponentType& GetComponent(const Entity a_Entity);
        /**
         * @brief Remove a component from an entity
         * @params a_Entity The entity to remove the component from
         */
        template<typename ComponentType>
        void RemoveComponent(Entity a_Entity);
        /**
         * @brief Gets the ID of a component type
         * @returns The ID of a component type
         */
        template<typename ComponentType>
        ComponentTypeID GetComponentTypeID();


        /** SystemManager **/

        /**
         * @brief Register a new system
         * @params a_ComponentManager The ComponentManager this system is used on
         * @returns The created system
         */
        template<typename SystemType>
        tabi::shared_ptr<SystemType> RegisterSystem();
        /**
         * @brief Set whether a component type is required or not for a system
         * @params a_Required True if the system requires the component, false if not
         */
        template<typename SystemType, typename ComponentType>
        void SetComponentTypeRequired(bool a_Required);
        /**
         * @brief Set the signature of a system
         * @params a_Signature The signature to apply to the system
         */
        template<typename SystemType>
        void SetSystemSignature(const SystemSignature& a_Signature);
        /**
         * @brief Updates all registered systems
         * @params a_DeltaTime The time between the previous update and this update
         */
        void Update(float a_DeltaTime);

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
    inline ComponentTypeID ECS::GetComponentTypeID()
    {
        return m_ComponentManager->GetComponentTypeID<ComponentType>();
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
    inline tabi::shared_ptr<SystemType> ECS::RegisterSystem()
    {
        return std::move(m_SystemManager->RegisterSystem<SystemType>(m_ComponentManager.get()));
    }

    template<typename SystemType, typename ComponentType>
    inline void ECS::SetComponentTypeRequired(bool a_Required)
    {
        auto systemSig = m_SystemManager->GetSystemSignature<SystemType>();
        

        systemSig.set(m_ComponentManager->GetComponentTypeID<ComponentType>(), a_Required);
        
       SetSystemSignature<SystemType>(systemSig);
    }
    
    template<typename SystemType>
    inline void ECS::SetSystemSignature(const SystemSignature& a_Signature)
    {
        m_SystemManager->SetSystemSignature<SystemType>(a_Signature);
    }
}

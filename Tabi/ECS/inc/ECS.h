#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

#include <TabiPointers.h>

namespace tabi
{
    class EntityManager;
    class ComponentManager;
    class SystemManager;

    class ECS
    {
    public:
        ECS();
        ECS(const ECS&) = delete;
        ECS(ECS&) = delete;
        
        ~ECS() = default;

        // EntityManager
        Entity CreateEntity();
        void DestroyEntity(Entity::ID_t a_EntityID);
        EntitySignature GetSignature(const Entity::ID_t a_EntityID);
        void SetSignature(const Entity::ID_t a_EntityID, const EntitySignature& a_Signature);

        // ComponentManager
        template<typename ComponentType>
        void AddComponent(const Entity::ID_t a_EntityID, ComponentType& a_Component);
        template<typename ComponentType>
        ComponentType& GetComponent(const Entity::ID_t a_EntityID);
        template<typename ComponentType>
        void RemoveComponent(Entity::ID_t a_EntityID);

        // SystemManager
        template<typename SystemType>
        tabi::shared_ptr<SystemType> RegisterSystem();
        template<typename SystemType>
        void SetSystemSignature(const SystemSignature& a_Signature);
        void Update(float a_DeltaTime);

    private:
        tabi::unique_ptr<EntityManager> m_EntityManager;
        tabi::unique_ptr<ComponentManager> m_ComponentManager;
        tabi::unique_ptr<SystemManager> m_SystemManager;
    };

    template<typename ComponentType>
    inline void ECS::AddComponent(const Entity::ID_t a_EntityID, ComponentType& a_Component)
    {
        m_ComponentManager->AddComponent(a_EntityID, a_Component);
        
        auto sig = m_EntityManager->GetSignature(a_EntityID);
        sig.set(m_ComponentManager->GetComponentType<ComponentType>());
        m_EntityManager->SetSignature(a_EntityID, sig);
        
        m_SystemManager->OnEntitySignatureChanged(a_EntityID, sig);
    }

    template<typename ComponentType>
    inline ComponentType& ECS::GetComponent(const Entity::ID_t a_EntityID)
    {
        return m_ComponentManager->GetComponent<ComponentType>(a_EntityID);
    }

    template<typename ComponentType>
    inline void ECS::RemoveComponent(Entity::ID_t a_EntityID)
    {
        m_ComponentManager->RemoveComponent<ComponentType>(a_EntityID);
        
        auto sig = m_EntityManager->GetSignature(a_EntityID);
        sig.set(m_ComponentManager->GetComponentType<ComponentType>(), false);
        m_EntityManager->SetSignature(a_EntityID, sig);

        m_SystemManager->OnEntitySignatureChanged(a_EntityID, sig);
    }

    template<typename SystemType>
    inline tabi::shared_ptr<SystemType> ECS::RegisterSystem()
    {
        return std::move(m_SystemManager->RegisterSystem<SystemType>(m_ComponentManager.get()));
    }
    
    template<typename SystemType>
    inline void ECS::SetSystemSignature(const SystemSignature& a_Signature)
    {
        m_SystemManager-?SetSystemSignature<SystemType>(a_Signature);
    }
}
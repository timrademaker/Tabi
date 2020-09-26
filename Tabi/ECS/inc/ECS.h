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

        // EntityManager
        Entity CreateEntity();
        void DestroyEntity(Entity a_Entity);
        EntitySignature GetSignature(const Entity a_Entity);
        void SetSignature(const Entity a_Entity, const EntitySignature& a_Signature);

        // ComponentManager
        template<typename ComponentType>
        void AddComponent(const Entity a_Entity, ComponentType a_Component);
        template<typename ComponentType>
        ComponentType& GetComponent(const Entity a_Entity);
        template<typename ComponentType>
        ComponentTypeID GetComponentTypeID();
        template<typename ComponentType>
        void RemoveComponent(Entity a_Entity);

        // SystemManager
        template<typename SystemType>
        tabi::shared_ptr<SystemType> RegisterSystem();
        template<typename SystemType, typename ComponentType>
        void SetComponentTypeRequired(bool a_Required);
        template<typename SystemType>
        void SetSystemSignature(const SystemSignature& a_Signature);
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

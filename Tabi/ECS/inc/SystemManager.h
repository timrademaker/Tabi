#pragma once

#include "Entity.h"
#include "ISystem.h"

#include <TabiContainers.h>
#include <TabiPointers.h>
#include <cassert>

namespace tabi
{
    using SystemSignature = bitset<MAX_COMPONENTS>;

    class Entity;

    class SystemManager
    {
        using SystemTypeHash = const char*;

    public:
        template<typename SystemType>
        tabi::shared_ptr<SystemType> RegisterSystem(ComponentManager* a_ComponentManager);

        template<typename SystemType>
        SystemSignature GetSystemSignature();
        template<typename SystemType>
        void SetSystemSignature(const SystemSignature& a_Signature);

        void OnEntityDestroyed(const Entity::ID_t a_EntityID);
        void OnEntitySignatureChanged(const Entity::ID_t a_EntityID, EntitySignature a_Signature);

        void Update(float a_DeltaTime);

    private:
        template<typename SystemType>
        static SystemTypeHash CreateHash();

    private:
        tabi::map<SystemTypeHash, tabi::shared_ptr<ISystem>> m_Systems;
        tabi::map<SystemTypeHash, SystemSignature> m_SystemSignatures;


    };

    template <typename SystemType>
    tabi::shared_ptr<SystemType> SystemManager::RegisterSystem(ComponentManager* a_ComponentManager)
    {
        const SystemTypeHash hash = CreateHash<SystemType>();

        // Check if the system has already been registered
        assert(m_Systems.find(hash) == m_Systems.end());

        auto system = tabi::make_shared<SystemType>(a_ComponentManager);
        m_Systems.insert(tabi::make_pair(hash, system));

        return system;
    }

    template<typename SystemType>
    inline SystemSignature SystemManager::GetSystemSignature()
    {
        const SystemTypeHash hash = CreateHash<SystemType>();

        // Check if the system exists;
        assert(m_Systems.find(hash) != m_Systems.end());

        return m_SystemSignatures[hash];
    }

    template <typename SystemType>
    inline void SystemManager::SetSystemSignature(const SystemSignature& a_Signature)
    {
        const SystemTypeHash hash = CreateHash<SystemType>();

        // Check if the system exists;
        assert(m_Systems.find(hash) != m_Systems.end());

        m_SystemSignatures[hash] = a_Signature;
    }

    template <typename SystemType>
    inline SystemManager::SystemTypeHash SystemManager::CreateHash()
    {
        return typeid(SystemType).name();
    }
}

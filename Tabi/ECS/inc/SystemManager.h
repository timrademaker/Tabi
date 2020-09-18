#pragma once

#include "Entity.h"
#include "ISystem.h"

#include <TabiContainers.h>
#include <TabiPointers.h>
#include <cassert>

namespace tabi
{
    class Entity;

    class SystemManager
    {
        using SystemTypeHash = const char*;

    public:
        template<typename SystemType>
        tabi::shared_ptr<SystemType> RegisterSystem();

        template<typename SystemType>
        void SetSystemSignature(const SystemSignature& a_Signature);

        void OnEntityDestroyed(const Entity& a_Entity);
        void OnEntitySignatureChanged(const Entity& a_Entity, EntitySignature a_Signature);

    private:
        template<typename SystemType>
        static SystemTypeHash CreateHash();

    private:
        tabi::map<SystemTypeHash, tabi::shared_ptr<ISystem>> m_Systems;
        tabi::map<SystemTypeHash, SystemSignature> m_SystemSignatures;


    };

    template <typename SystemType>
    tabi::shared_ptr<SystemType> SystemManager::RegisterSystem()
    {
        const SystemTypeHash hash = CreateHash<SystemType>();

        // Check if the system has already been registered
        assert(m_Systems.find(hash) == m_Systems.end());

        auto system = tabi::make_shared<SystemType>();
        m_Systems.insert({ hash, system });

        return system;
    }

    template <typename SystemType>
    void SystemManager::SetSystemSignature(const SystemSignature& a_Signature)
    {
        const SystemTypeHash hash = CreateHash<SystemType>();

        // Check if the system exists;
        assert(m_Systems.find(hash) != m_Systems.end());

        m_SystemSignatures[hash] = a_Signature;
    }

    template <typename SystemType>
    SystemManager::SystemTypeHash SystemManager::CreateHash()
    {
        return typeid(SystemType).name();
    }
}

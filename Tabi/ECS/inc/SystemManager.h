#pragma once

#include "Entity.h"
#include "ISystem.h"

#include <TabiContainers.h>
#include <TabiPointers.h>

namespace tabi
{
    class Entity;

    class SystemManager
    {
        using SystemTypeHash = const char*;

    public:
        template<typename SystemType>
        void RegisterSystemType();

        void OnEntityDestroyed(const Entity& a_Entity);
        void OnEntitySignatureChanged(const Entity& a_Entity, EntitySignature a_Signature);

    private:
        tabi::map<SystemTypeHash, tabi::shared_ptr<ISystem>> m_Systems;
        tabi::map<SystemTypeHash, SystemSignature> m_SystemSignatures;


    };
}

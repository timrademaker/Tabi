#include "SystemManager.h"

using namespace tabi;

void SystemManager::OnEntityDestroyed(const Entity& a_Entity)
{
    for(const auto& pair : m_Systems)
    {
        pair.second->m_Entities.erase(a_Entity.m_ID);
    }
}

void SystemManager::OnEntitySignatureChanged(const Entity& a_Entity, EntitySignature a_Signature)
{
    for(const auto& pair : m_Systems)
    {
        const auto& hash = pair.first;
        const auto& system = pair.second;
        const auto& systemSignature = m_SystemSignatures[hash];

        if((a_Signature & systemSignature) == systemSignature)
        {
            system->m_Entities.insert(a_Entity.m_ID);
        }
        else
        {
            system->m_Entities.erase(a_Entity.m_ID);
        }
    }
}

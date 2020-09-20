#include "SystemManager.h"

using namespace tabi;

void SystemManager::OnEntityDestroyed(const Entity::ID_t a_EntityID)
{
    for(const auto& pair : m_Systems)
    {
        pair.second->m_Entities.erase(a_EntityID);
    }
}

void SystemManager::OnEntitySignatureChanged(const Entity::ID_t a_EntityID, EntitySignature a_Signature)
{
    for(const auto& pair : m_Systems)
    {
        const auto& hash = pair.first;
        const auto& system = pair.second;
        const auto& systemSignature = m_SystemSignatures[hash];

        if((a_Signature & systemSignature) == systemSignature)
        {
            system->m_Entities.insert(a_EntityID);
        }
        else
        {
            system->m_Entities.erase(a_EntityID);
        }
    }
}

void tabi::SystemManager::Update(float a_DeltaTime)
{
    for (const auto& pair : m_Systems)
    {
        pair.second->OnUpdate(a_DeltaTime);
    }
}

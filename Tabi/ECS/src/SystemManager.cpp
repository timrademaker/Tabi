#include "SystemManager.h"

using namespace tabi;

void SystemManager::OnEntityDestroyed(const Entity a_Entity)
{
    for(const auto& pair : m_Systems)
    {
        pair.second->RemoveEntity(a_Entity);
    }
}

void SystemManager::OnEntitySignatureChanged(const Entity a_Entity, EntitySignature a_Signature)
{
    for(const auto& pair : m_Systems)
    {
        const auto& system = pair.second;
        const auto& systemSignature = system->GetSystemSignature();

        if((a_Signature & systemSignature) == systemSignature)
        {
            system->AddEntity(a_Entity);
        }
        else
        {
            system->RemoveEntity(a_Entity);
        }
    }
}

void tabi::SystemManager::Update(float a_DeltaTime) const
{
    for (const auto& pair : m_Systems)
    {
        pair.second->OnUpdate(a_DeltaTime);
    }
}

void SystemManager::Render() const
{
    for (const auto& pair : m_Systems)
    {
        pair.second->OnRender();
    }
}

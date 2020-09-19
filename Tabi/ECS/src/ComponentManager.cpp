#include "ComponentManager.h"

using namespace tabi;

void tabi::ComponentManager::OnEntityDestroyed(const Entity::ID_t a_EntityID)
{
    for (const auto& pair : m_ComponentArrays)
    {
        pair.second->OnEntityDestroyed(a_EntityID);
    }
}

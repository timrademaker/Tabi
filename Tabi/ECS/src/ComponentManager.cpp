#include "ComponentManager.h"

using namespace tabi;

void tabi::ComponentManager::OnEntityDestroyed(const Entity a_Entity)
{
    for (const auto& pair : m_ComponentArrays)
    {
        pair.second->OnEntityDestroyed(a_Entity);
    }
}

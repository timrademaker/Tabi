#include "ComponentManager.h"

using namespace tabi;

void tabi::ComponentManager::OnEntityDestroyed(const Entity a_Entity) const
{
    for (const auto& pair : m_ComponentArrays)
    {
        pair.second->OnEntityDestroyed(a_Entity);
    }
}

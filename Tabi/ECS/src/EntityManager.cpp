#include "EntityManager.h"

#include "ECS_Constants.h"

#include <TabiMacros.h>


using namespace tabi;

tabi::EntityManager::EntityManager()
{
    for (size_t id = 0; id < MAX_ENTITIES; ++id)
    {
        m_AvailableIDs.push(id);
    }
}

Entity tabi::EntityManager::CreateEntity()
{
    // Make sure there's still an available ID for a new entity
    TABI_ASSERT(!m_AvailableIDs.empty());
    
    Entity ent;
    ent = m_AvailableIDs.front();
    m_AvailableIDs.pop();

    return ent;
}

void tabi::EntityManager::DestroyEntity(Entity& a_Entity)
{
    // Check if the entity ID is in range
    TABI_ASSERT(a_Entity < MAX_ENTITIES);

    m_EntitySignatures[a_Entity].reset();
    m_AvailableIDs.push(a_Entity);

    a_Entity = INVALID_ENTITY_ID;
}

EntitySignature tabi::EntityManager::GetEntitySignature(const Entity a_Entity)
{
    // Check if the entity ID is in range
    TABI_ASSERT(a_Entity < MAX_ENTITIES);

    return m_EntitySignatures[a_Entity];
}

void tabi::EntityManager::SetSignature(const Entity a_Entity, const EntitySignature& a_Signature)
{
    // Check if the entity ID is in range
    TABI_ASSERT(a_Entity < MAX_ENTITIES);

    m_EntitySignatures[a_Entity] = a_Signature;
}
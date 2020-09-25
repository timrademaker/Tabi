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
    ent.m_ID = m_AvailableIDs.front();
    m_AvailableIDs.pop();

    return ent;
}

void tabi::EntityManager::DestroyEntity(Entity& a_Entity)
{
    DestroyEntity(a_Entity.m_ID);
}

void tabi::EntityManager::DestroyEntity(Entity::ID_t& a_EntityID)
{
    // Check if the entity ID is in range
    TABI_ASSERT(a_EntityID < MAX_ENTITIES);

    m_EntitySignatures[a_EntityID].reset();
    m_AvailableIDs.push(a_EntityID);

    a_EntityID = INVALID_ENTITY_ID;
}

EntitySignature tabi::EntityManager::GetSignature(const Entity& a_Entity)
{
    return GetSignature(a_Entity.m_ID);
}

EntitySignature tabi::EntityManager::GetSignature(const Entity::ID_t a_EntityID)
{
    // Check if the entity ID is in range
    TABI_ASSERT(a_EntityID < MAX_ENTITIES);

    return m_EntitySignatures[a_EntityID];
}

void tabi::EntityManager::SetSignature(const Entity& a_Entity, const EntitySignature& a_Signature)
{
    SetSignature(a_Entity.m_ID, a_Signature);
}

void tabi::EntityManager::SetSignature(const Entity::ID_t a_EntityID, const EntitySignature& a_Signature)
{
    // Check if the entity ID is in range
    TABI_ASSERT(a_EntityID < MAX_ENTITIES);

    m_EntitySignatures[a_EntityID] = a_Signature;
}
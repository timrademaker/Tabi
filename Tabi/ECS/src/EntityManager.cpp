#include "EntityManager.h"

#include "ECS_Constants.h"

#include <cassert>

using namespace tabi;

tabi::EntityManager::EntityManager()
    : m_LivingEntityCount(0)
{
    for (size_t id = 0; id < MAX_ENTITIES; ++id)
    {
        m_AvailableIDs.push(id);
    }
}

Entity tabi::EntityManager::CreateEntity()
{
    // Make sure there's still an available slot for an entity to be created
    assert(m_LivingEntityCount < MAX_ENTITIES);
    
    Entity ent;

    ent.m_ID = m_AvailableIDs.front();
    m_AvailableIDs.pop();
    ++m_LivingEntityCount;

    return ent;
}

void tabi::EntityManager::DestroyEntity(Entity& a_Entity)
{
    DestroyEntity(a_Entity.m_ID);
}

void tabi::EntityManager::DestroyEntity(Entity::ID_t& a_EntityID)
{
    // Check if the entity ID is in range
    assert(a_EntityID < MAX_ENTITIES);

    m_EntitySignatures[a_EntityID].reset();
    m_AvailableIDs.push(a_EntityID);
    --m_LivingEntityCount;

    a_EntityID = INVALID_ENTITY_ID;
}

EntitySignature tabi::EntityManager::GetSignature(const Entity& a_Entity)
{
    return GetSignature(a_Entity.m_ID);
}

EntitySignature tabi::EntityManager::GetSignature(const Entity::ID_t a_EntityID)
{
    // Check if the entity ID is in range
    assert(a_EntityID < MAX_ENTITIES);

    return m_EntitySignatures[a_EntityID];
}

void tabi::EntityManager::SetSignature(const Entity& a_Entity, const EntitySignature& a_Signature)
{
    SetSignature(a_Entity.m_ID, a_Signature);
}

void tabi::EntityManager::SetSignature(const Entity::ID_t a_EntityID, const EntitySignature& a_Signature)
{
    // Check if the entity ID is in range
    assert(a_EntityID < MAX_ENTITIES);

    m_EntitySignatures[a_EntityID] = a_Signature;
}
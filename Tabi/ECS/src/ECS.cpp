#include "ECS.h"

using namespace tabi;

tabi::ECS::ECS()
{
     m_EntityManager = tabi::make_unique<EntityManager>();
     m_ComponentManager = tabi::make_unique<ComponentManager>();
     m_SystemManager = tabi::make_unique<SystemManager>();
}

tabi::Entity tabi::ECS::CreateEntity()
{
    return m_EntityManager->CreateEntity();
}

void tabi::ECS::DestroyEntity(Entity::ID_t a_EntityID)
{
    m_ComponentManager->OnEntityDestroyed(a_EntityID);
    m_SystemManager->OnEntityDestroyed(a_EntityID);

    m_EntityManager->DestroyEntity(a_EntityID);
}

tabi::EntitySignature tabi::ECS::GetSignature(const Entity::ID_t a_EntityID)
{
    return m_EntityManager->GetSignature(a_EntityID);
}

void tabi::ECS::SetSignature(const Entity::ID_t a_EntityID, const EntitySignature& a_Signature)
{
    m_EntityManager->SetSignature(a_EntityID, a_Signature);
    m_SystemManager->OnEntitySignatureChanged(a_EntityID, a_Signature);
}

void tabi::ECS::Update(float a_DeltaTime)
{
    m_SystemManager->Update(a_DeltaTime);
}


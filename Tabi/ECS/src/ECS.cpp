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

void tabi::ECS::DestroyEntity(Entity& a_Entity)
{
    m_ComponentManager->OnEntityDestroyed(a_Entity);
    m_SystemManager->OnEntityDestroyed(a_Entity);

    m_EntityManager->DestroyEntity(a_Entity);
}

tabi::EntitySignature tabi::ECS::GetEntitySignature(const Entity a_Entity)
{
    return m_EntityManager->GetSignature(a_Entity);
}

void tabi::ECS::SetEntitySignature(const Entity a_Entity, const EntitySignature& a_Signature)
{
    m_EntityManager->SetSignature(a_Entity, a_Signature);
    m_SystemManager->OnEntitySignatureChanged(a_Entity, a_Signature);
}

void tabi::ECS::Update(float a_DeltaTime)
{
    m_SystemManager->Update(a_DeltaTime);
}


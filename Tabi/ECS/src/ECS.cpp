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

tabi::EntitySignature tabi::ECS::GetEntitySignature(const Entity a_Entity) const
{
    return m_EntityManager->GetSignature(a_Entity);
}

void tabi::ECS::Update(float a_DeltaTime) const
{
    m_SystemManager->Update(a_DeltaTime);
}

void ECS::Render() const
{
    m_SystemManager->Render();
}


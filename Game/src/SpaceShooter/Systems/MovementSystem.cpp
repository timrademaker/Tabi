#include "Systems/MovementSystem.h"

#include "Components/MovementComponent.h"

#include <ComponentManager.h>
#include <Components/Transform.h>

void SpaceShooter::MovementSystem::OnUpdate(float a_DeltaTime)
{
    for (auto& ent : m_Entities)
    {
        auto& trans = m_ComponentManager->GetComponent<tabi::Transform>(ent);
        auto& vel = m_ComponentManager->GetComponent<MovementComponent>(ent);

        trans.m_Position += vel.m_Velocity * a_DeltaTime;
    }
}

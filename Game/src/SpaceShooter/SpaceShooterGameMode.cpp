#include "SpaceShooter/SpaceShooterGameMode.h"

#include "Systems/MovementSystem.h"
#include <Components/Transform.h>


bool SpaceShooter::SpaceShooterGameMode::OnInitialize()
{
    m_ECS.RegisterSystem<SpaceShooter::MovementSystem>();
    m_ECS.SetComponentTypeRequired<SpaceShooter::MovementSystem, tabi::Transform>(true);

    return true;
}

void SpaceShooter::SpaceShooterGameMode::OnUpdate(float a_DeltaTime)
{
    m_ECS.Update(a_DeltaTime);
}

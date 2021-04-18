#include "SpaceShooter/SpaceShooterGameMode.h"

#include "Systems/MovementSystem.h"
#include "Systems/StaticMeshRendererSystem.h"


#include "Components/MovementComponent.h"
#include <Components/Transform.h>

#include <Components/StaticMeshComponent.h>

#include <InputManager.h>
#include <IRenderer.h>
#include <ResourceManager.h>

bool SpaceShooter::SpaceShooterGameMode::OnInitialize()
{
    auto& renderer = tabi::graphics::IRenderer::GetInstance();

    m_ECS.RegisterSystem<SpaceShooter::MovementSystem>();
    m_ECS.SetComponentTypeRequired<SpaceShooter::MovementSystem, SpaceShooter::MovementComponent>(true);
    m_ECS.SetComponentTypeRequired<SpaceShooter::MovementSystem, tabi::Transform>(true);


    // TODO: This shouldn't really be in game code, so find a way of having systems register themselves?
    m_ECS.RegisterSystem<tabi::StaticMeshRenderSystem>();
    m_ECS.SetComponentTypeRequired<tabi::StaticMeshRenderSystem, tabi::StaticMeshComponent>(true);
    m_ECS.SetComponentTypeRequired<tabi::StaticMeshRenderSystem, tabi::Transform>(true);


    tabi::Entity ent = m_ECS.CreateEntity();
    tabi::Transform tr;
    tr.m_Scale = tabi::vec3{ 0.01f, 0.01f, 0.01f };
    m_ECS.AddComponent<tabi::Transform>(ent, tr);

    tabi::StaticMeshComponent smc;
    auto duck = tabi::ResourceManager::GetInstance().LoadResource<tabi::Mesh>("Assets/Duck.glb");
    smc.m_Mesh = duck;

    m_ECS.AddComponent<tabi::StaticMeshComponent>(ent, smc);

    m_ECS.AddComponent<SpaceShooter::MovementComponent>(ent, SpaceShooter::MovementComponent{ {1.0f, 0.0f, 0.0f} });

    m_Camera = tabi::make_shared<tabi::Camera>();
    m_Camera->MoveTo(tabi::vec3{ 0.0f, 0.0f, -10.0f });
    m_Camera->LookAt(tabi::vec3{ 0.0f, 0.0f, 0.0f });

    renderer.UseCamera(m_Camera);

    tabi::InputManager::SetCursorVisible(false);
    tabi::InputManager::SetCursorCapture(true);

    return true;
}

void SpaceShooter::SpaceShooterGameMode::OnUpdate(float a_DeltaTime)
{
    m_ECS.Update(a_DeltaTime);
}

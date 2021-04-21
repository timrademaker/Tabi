#include "SpaceShooter/SpaceShooterGameMode.h"

#include "Entities/Player.h"

#include "Components/GunComponent.h"
#include "Components/MovementComponent.h"

#include "Systems/MovementSystem.h"
#include "Systems/GunSystem.h"

#include <Application.h>

#include <Components/Transform.h>
#include <Components/StaticMeshComponent.h>
#include <Components/TagComponent.h>
#include <Systems/StaticMeshRendererSystem.h>

#include <InputManager.h>
#include <IRenderer.h>
#include <ResourceManager.h>


SpaceShooter::SpaceShooterGameMode::~SpaceShooterGameMode()
{
    if (m_Player)
    {
        delete m_Player;
    }
}

bool SpaceShooter::SpaceShooterGameMode::OnInitialize()
{
    auto& renderer = tabi::graphics::IRenderer::GetInstance();

    m_ECS.RegisterSystem<SpaceShooter::MovementSystem>();
    m_ECS.SetComponentTypeRequired<SpaceShooter::MovementSystem, SpaceShooter::MovementComponent>(true);
    m_ECS.SetComponentTypeRequired<SpaceShooter::MovementSystem, tabi::Transform>(true);

    tabi::shared_ptr<SpaceShooter::GunSystem> gs = m_ECS.RegisterSystem<SpaceShooter::GunSystem>();
    gs->SetECS(&m_ECS);
    m_ECS.SetComponentTypeRequired<SpaceShooter::GunSystem, SpaceShooter::GunComponent>(true);
    m_ECS.SetComponentTypeRequired<SpaceShooter::GunSystem, tabi::Transform>(true);

    // TODO: This shouldn't really be in game code, so find a way of having systems register themselves?
    m_ECS.RegisterSystem<tabi::StaticMeshRenderSystem>();
    m_ECS.SetComponentTypeRequired<tabi::StaticMeshRenderSystem, tabi::StaticMeshComponent>(true);
    m_ECS.SetComponentTypeRequired<tabi::StaticMeshRenderSystem, tabi::Transform>(true);

    m_Player = new Player(&m_ECS);


    tabi::Entity ent = m_ECS.CreateEntity();
    tabi::Transform tr;
    tr.m_Scale = tabi::vec3{ 0.01f, 0.01f, 0.01f };
    m_ECS.AddComponent(ent, tr);

    tabi::StaticMeshComponent smc;
    auto duck = tabi::ResourceManager::GetInstance().LoadResource<tabi::Mesh>("Assets/Duck.glb");
    smc.m_Mesh = duck;

    m_ECS.AddComponent(ent, smc);

    m_ECS.AddComponent(ent, SpaceShooter::MovementComponent{ {1.0f, 0.0f, 0.0f} });

    m_Camera = tabi::make_shared<tabi::Camera>();
    m_Camera->MoveTo(tabi::vec3{ 0.0f, 0.0f, 10.0f });
    m_Camera->LookAt(tabi::vec3{ 0.0f, 0.0f, 0.0f });

    renderer.UseCamera(m_Camera);

    tabi::InputManager::SetCursorVisible(false);
    tabi::InputManager::SetCursorCapture(true);

    return true;
}

void SpaceShooter::SpaceShooterGameMode::OnUpdate(float a_DeltaTime)
{
    m_ECS.Update(a_DeltaTime);
    m_Player->Update(a_DeltaTime);
}

void SpaceShooter::SpaceShooterGameMode::OnGameOver()
{
    tabi::Application::Get().ExitGame();
}

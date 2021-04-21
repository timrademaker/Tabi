#include "Entities/Player.h"

#include "Components/GunComponent.h"
#include "Components/HealthComponent.h"

#include <Math/vec3.h>

#include <ECS.h>

#include <Components/Transform.h>
#include <Components/StaticMeshComponent.h>
#include <Components/TagComponent.h>

#include <ResourceManager.h>

#include <InputManager.h>
#include <Enums/EKeyboard.h>


SpaceShooter::Player::Player(tabi::ECS* a_ECS)
    : m_ECS(a_ECS), m_CurrentRespawnTimer(0), m_IsPendingRespawn(false), m_Score(0), m_RemainingLives(s_StartingLives)
{
    SetUpPlayerEntity();

    SetUpPlayerInput();
}

void SpaceShooter::Player::Update(const float a_DeltaTime)
{
    m_DeltaTime = a_DeltaTime;

    if (m_IsPendingRespawn)
    {
        m_CurrentRespawnTimer -= a_DeltaTime;

        if (m_CurrentRespawnTimer <= 0.0f)
        {
            Respawn();
        }
    }
}

void SpaceShooter::Player::OnDeath()
{
    m_IsPendingRespawn = true;
    m_CurrentRespawnTimer = s_RespawnDelay;

    // Get mesh and set to hidden
    auto& mesh = m_ECS->GetComponent<tabi::StaticMeshComponent>(m_PlayerEntity);
    mesh.m_IsEnabled = false;

    m_RemainingLives -= 1;

    if (m_RemainingLives < 0)
    {
        m_OnGameOver.Broadcast();
    }
}

void SpaceShooter::Player::MoveLeft(tabi::ButtonEvent)
{
    auto& transform = m_ECS->GetComponent<tabi::Transform>(m_PlayerEntity);

    transform.m_Position -= tabi::vec3{ s_MovementSpeed * m_DeltaTime, 0.0f, 0.0f };
}

void SpaceShooter::Player::MoveRight(tabi::ButtonEvent)
{
    auto& transform = m_ECS->GetComponent<tabi::Transform>(m_PlayerEntity);

    transform.m_Position += tabi::vec3{ s_MovementSpeed * m_DeltaTime, 0.0f, 0.0f };
}

void SpaceShooter::Player::MoveUp(tabi::ButtonEvent)
{
    auto& transform = m_ECS->GetComponent<tabi::Transform>(m_PlayerEntity);

    transform.m_Position += tabi::vec3{ 0.0f, s_MovementSpeed * m_DeltaTime, 0.0f };
}

void SpaceShooter::Player::MoveDown(tabi::ButtonEvent)
{
    auto& transform = m_ECS->GetComponent<tabi::Transform>(m_PlayerEntity);

    transform.m_Position -= tabi::vec3{ 0.0f, s_MovementSpeed * m_DeltaTime, 0.0f };
}

void SpaceShooter::Player::Shoot(tabi::ButtonEvent)
{
    auto& gun = m_ECS->GetComponent<SpaceShooter::GunComponent>(m_PlayerEntity);
    gun.PrepareShot();
}

void SpaceShooter::Player::SetUpPlayerEntity()
{
    m_PlayerEntity = m_ECS->CreateEntity();

    // Transform
    tabi::Transform tr;
    tr.m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };
    tr.m_Scale = tabi::vec3{ 0.01f, 0.01f, 0.01f };
    tr.m_EulerRotation = tabi::vec3{ 0.0f, 1.57079633f, 0.0f };
    m_ECS->AddComponent(m_PlayerEntity, tr);

    // Mesh
    tabi::StaticMeshComponent smc;
    auto duck = tabi::ResourceManager::GetInstance().LoadResource<tabi::Mesh>(s_PlayerMesh);
    smc.m_Mesh = duck;
    smc.m_RelativeMeshRotation = tabi::vec3{ 0.0f, 1.57079633f, 0.0f };

    m_ECS->AddComponent(m_PlayerEntity, smc);

    // Tag
    tabi::TagComponent tags;
    tags.AddTag("Player");
    m_ECS->AddComponent(m_PlayerEntity, tags);

    // Gun
    SpaceShooter::GunComponent gun;
    gun.m_AmmoCount = -1;
    gun.m_BulletInfo = SpaceShooter::BulletInfoFactory::CreateBulletInfo(SpaceShooter::EBulletType::Bullet);
    gun.m_ShotCooldown = 1.0f;
    m_ECS->AddComponent(m_PlayerEntity, gun);

    // Health
    SpaceShooter::HealthComponent health(3, [this]()
        {
            this->OnDeath();
        });
    m_ECS->AddComponent(m_PlayerEntity, health);
}

void SpaceShooter::Player::SetUpPlayerInput()
{
    // Keyboard
    tabi::InputManager::BindButton(tabi::EKeyboard::A, this, &Player::MoveLeft);
    tabi::InputManager::BindButton(tabi::EKeyboard::D, this, &Player::MoveRight);
    tabi::InputManager::BindButton(tabi::EKeyboard::W, this, &Player::MoveUp);
    tabi::InputManager::BindButton(tabi::EKeyboard::S, this, &Player::MoveDown);
    tabi::InputManager::BindButton(tabi::EKeyboard::SPACE, this, &Player::Shoot);
}

void SpaceShooter::Player::Respawn()
{
    m_IsPendingRespawn = false;

    // Get mesh and set to visible
    auto& mesh = m_ECS->GetComponent<tabi::StaticMeshComponent>(m_PlayerEntity);
    mesh.m_IsEnabled = true;
}

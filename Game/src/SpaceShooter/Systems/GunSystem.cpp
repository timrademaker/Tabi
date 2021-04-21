#include "Systems/GunSystem.h"

#include "Components/BulletComponent.h"
#include "Components/GunComponent.h"
#include "Components/MovementComponent.h"

#include <Components/StaticMeshComponent.h>
#include <Components/Transform.h>
#include <Components/TagComponent.h>
#include <ECS.h>

#include <Logging.h>

tabi::vec3 SpaceShooter::GunSystem::s_BulletScale = tabi::vec3{ 1.0f, 1.0f, 1.0f };

SpaceShooter::GunSystem::GunSystem(tabi::ComponentManager* a_ComponentManager)
    : ISystem(a_ComponentManager), m_ECS(nullptr)
{
}

void SpaceShooter::GunSystem::SetECS(tabi::ECS* a_ECS)
{
    m_ECS = a_ECS;
}

void SpaceShooter::GunSystem::OnUpdate(float a_DeltaTime)
{
    for (auto& ent : m_Entities)
    {
        auto& gun = m_ComponentManager->GetComponent<SpaceShooter::GunComponent>(ent);

        if (gun.m_HasPendingShot)
        {
            ShootBullet(gun.m_BulletInfo, ent);

            gun.m_HasPendingShot = false;
        }

        gun.m_CurrentShotCooldown -= a_DeltaTime;
    }
}

void SpaceShooter::GunSystem::ShootBullet(const BulletInfo& a_BulletInfo, const tabi::Entity a_Entity)
{
    if (!m_ECS)
    {
        tabi::logger::Log(tabi::logger::ELogLevel::Warning, "ECS was not set up for GunSystem! Please use SetECS to set it.");
        return;
    }

    auto& entityTransform = m_ComponentManager->GetComponent<tabi::Transform>(a_Entity);

    // Create bullet
    tabi::Entity bullet = m_ECS->CreateEntity();

    // Add transform
    tabi::Transform bulletTransform;
    bulletTransform.m_Position = entityTransform.m_Position;
    bulletTransform.m_EulerRotation = entityTransform.m_EulerRotation;
    bulletTransform.m_Scale = s_BulletScale;
    m_ECS->AddComponent(bullet, bulletTransform);

    // Add mesh
    tabi::StaticMeshComponent smc;
    smc.m_Mesh = a_BulletInfo.m_Mesh;
    m_ECS->AddComponent(bullet, smc);

    // Add movement component
    SpaceShooter::MovementComponent movement;
    movement.m_Velocity = tabi::mat4::SetRotation(tabi::mat4::Identity(), entityTransform.m_EulerRotation).GetForward() * a_BulletInfo.m_Velocity;
    m_ECS->AddComponent(bullet, movement);

    // Add bullet component
    BulletComponent bc;
    bc.m_Damage = a_BulletInfo.m_Damage;

    if (m_ComponentManager->GetComponent<tabi::TagComponent>(a_Entity).HasTag(s_PlayerTag))
    {
        bc.m_OwnerTag = s_PlayerTag;
    }
    else
    {
        bc.m_OwnerTag = s_EnemyTag;
    }

    m_ECS->AddComponent(bullet, bc);
}

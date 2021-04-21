#pragma once

#include "ISystem.h"

#include <Entity.h>

#include <Math/vec3.h>

namespace tabi
{
    class ECS;
}

namespace SpaceShooter
{

    class GunSystem : public tabi::ISystem
    {
    public:
        GunSystem(tabi::ComponentManager* a_ComponentManager);

        void SetECS(tabi::ECS* a_ECS);

        virtual void OnUpdate(float a_DeltaTime) override;

    private:
        void ShootBullet(const struct BulletInfo& a_BulletInfo, const tabi::Entity a_Entity);

    private:
        tabi::ECS* m_ECS;
        static constexpr const char* s_PlayerTag = "Player";
        static constexpr const char* s_EnemyTag = "Enemy";

        static tabi::vec3 s_BulletScale;
    };
}

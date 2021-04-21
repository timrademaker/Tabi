#pragma once

#include <Resources/Mesh.h>

namespace SpaceShooter
{
    struct BulletInfo
    {
        int m_Damage;
        float m_Velocity;
        tabi::shared_ptr<tabi::Mesh> m_Mesh;
    };

    enum class EBulletType
    {
        Bullet
    };

    class BulletInfoFactory
    {
    public:
        static BulletInfo CreateBulletInfo(const EBulletType a_BulletType);

    private:
        static tabi::shared_ptr<tabi::Mesh> GetMeshForBulletType(const EBulletType a_BulletType);

    private:
        static tabi::map<EBulletType, tabi::shared_ptr<tabi::Mesh>> s_BulletMeshes;
        static constexpr const char* s_BulletMeshPath = "Assets/Bullet.glb";
    };
}
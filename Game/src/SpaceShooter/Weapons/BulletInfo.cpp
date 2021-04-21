#include "Weapons/BulletInfo.h"

#include <ResourceManager.h>

tabi::map<SpaceShooter::EBulletType, tabi::shared_ptr<tabi::Mesh>> SpaceShooter::BulletInfoFactory::s_BulletMeshes;

SpaceShooter::BulletInfo SpaceShooter::BulletInfoFactory::CreateBulletInfo(const EBulletType a_BulletType)
{
    BulletInfo bi;

    switch (a_BulletType)
    {
    case EBulletType::Bullet:
    {
        bi.m_Damage = 1;
        bi.m_Velocity = 10.0f;
        bi.m_Mesh = GetMeshForBulletType(a_BulletType);
        break;
    }
    }

    return bi;
}

tabi::shared_ptr<tabi::Mesh> SpaceShooter::BulletInfoFactory::GetMeshForBulletType(const EBulletType a_BulletType)
{
    // Check if the mesh is already loaded
    const auto& bulletMesh = s_BulletMeshes.find(a_BulletType);
    if (bulletMesh != s_BulletMeshes.end())
    {
        return bulletMesh->second;
    }
    
    // Load mesh
    tabi::shared_ptr<tabi::Mesh> mesh = tabi::ResourceManager::GetInstance().LoadResource<tabi::Mesh>(s_BulletMeshPath, true, true);
    s_BulletMeshes.insert(tabi::make_pair(a_BulletType, mesh));

    return mesh;
}

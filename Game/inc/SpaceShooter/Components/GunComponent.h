#pragma once

#include "Weapons/BulletInfo.h"

namespace SpaceShooter
{
    class GunComponent
    {
    public:
        void PrepareShot();

    public:
        BulletInfo m_BulletInfo;
        
        float m_ShotCooldown;
        float m_CurrentShotCooldown;
        
        int m_AmmoCount;

        bool m_HasPendingShot = false;
    };
}

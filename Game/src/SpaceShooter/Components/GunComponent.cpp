#include "Components/GunComponent.h"

void SpaceShooter::GunComponent::PrepareShot()
{
    if (m_CurrentShotCooldown <= 0.0f && (m_AmmoCount > 0 || m_AmmoCount == -1))
    {
        m_HasPendingShot = true;
        m_CurrentShotCooldown = m_ShotCooldown;
    }
}

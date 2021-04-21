#pragma once

#include <TabiContainers.h>
#include <TabiMacros.h>
#include <TabiEvent.h>

namespace SpaceShooter
{
    class HealthComponent
    {
    public:
        HealthComponent() = default;
        HealthComponent(const int a_StartingHealth, tabi::EventSignature a_DestroyEntityFunction);

        TABI_INLINE void SetHealth(const int a_Health)
        {
            m_Health = a_Health;
        }

        TABI_INLINE void ApplyDamage(const int a_Damage)
        {
            m_Health -= a_Damage;
            
            if (!IsAlive())
            {
                m_OnDeath.Broadcast();
            }
        }

        TABI_INLINE bool IsAlive()
        {
            return m_Health > 0;
        }

    public:
        ::tabi::Event m_OnDeath;
    
    private:
        int m_Health;
    };
}

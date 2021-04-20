#include "Components/HealthComponent.h"

SpaceShooter::HealthComponent::HealthComponent(const int a_StartingHealth, tabi::EventSignature a_DestroyEntityFunction)
    : m_Health(a_StartingHealth)
{
    m_OnDeath.SubscribeStatic(a_DestroyEntityFunction);
}

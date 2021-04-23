#include "Colliders/ICollider.h"

tabi::ICollider::ICollider()
    : m_WorldPosition(tabi::vec3{0.0f, 0.0f, 0.0f})
{
}

tabi::ICollider::ICollider(const tabi::vec3& a_WorldPosition)
    : m_WorldPosition(a_WorldPosition)
{
}

void tabi::ICollider::SetWorldPosition(const tabi::vec3& a_WorldPosition)
{
    m_WorldPosition = a_WorldPosition;
}

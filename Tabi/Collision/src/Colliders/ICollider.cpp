#include "Colliders/ICollider.h"

#include <cfloat>

tabi::ICollider::ICollider()
    : m_Transform(tabi::Transform{}), m_BroadPhaseSphereRadius(FLT_MAX)
{
}

tabi::ICollider::ICollider(const Transform& a_WorldTransform)
    : m_Transform(a_WorldTransform), m_BroadPhaseSphereRadius(FLT_MAX)
{
}

tabi::ICollider::ICollider(const tabi::vec3& a_WorldPosition)
    : m_Transform(tabi::Transform{ a_WorldPosition }), m_BroadPhaseSphereRadius(FLT_MAX)
{
}

void tabi::ICollider::SetWorldPosition(const tabi::vec3& a_WorldPosition)
{
    m_Transform.m_Position = a_WorldPosition;
}

void tabi::ICollider::SetWorldScale(const vec3& a_WorldScale)
{
    m_Transform.m_Scale = a_WorldScale;
}

void tabi::ICollider::SetWorldRotation(const vec3& a_WorldRotation)
{
    m_Transform.m_EulerRotation = a_WorldRotation;
}

void tabi::ICollider::SetWorldTransfrom(const Transform& a_WorldTransform)
{
    m_Transform = a_WorldTransform;
}

tabi::vec3 tabi::ICollider::GetPosition() const
{
    return m_Transform.m_Position;
}

float tabi::ICollider::GetBroadPhaseRadius() const
{
    return m_BroadPhaseSphereRadius * m_Transform.m_Scale.MaxElement();
}

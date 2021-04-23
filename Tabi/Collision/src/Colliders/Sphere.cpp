#include "Colliders/Sphere.h"

tabi::SphereCollider::SphereCollider()
    : m_Radius(0), ICollider(tabi::vec3{ 0.0f, 0.0f, 0.0f })
{
}

tabi::SphereCollider::SphereCollider(const float a_Radius)
    : m_Radius(a_Radius), ICollider(tabi::vec3{ 0.0f, 0.0f, 0.0f })
{
}

tabi::SphereCollider::SphereCollider(const tabi::vec3& a_Center, const float a_Radius)
    : m_Radius(a_Radius), ICollider(a_Center)
{
}

tabi::vec3 tabi::SphereCollider::GetFurthestPointInDirection(const tabi::vec3& a_Direction) const
{
    return m_WorldPosition + vec3::Normalize(a_Direction) * m_Radius;
}

void tabi::SphereCollider::SetRadius(const float a_Radius)
{
    m_Radius = a_Radius;
}


#include "Colliders/Sphere.h"

tabi::SphereCollider::SphereCollider()
    : m_Radius(0), ICollider(tabi::vec3{ 0.0f, 0.0f, 0.0f })
{
}

tabi::SphereCollider::SphereCollider(const float a_Radius)
    : m_Radius(a_Radius), ICollider(tabi::vec3{ 0.0f, 0.0f, 0.0f })
{
}

tabi::SphereCollider::SphereCollider(const float a_Radius, const vec3& a_Center)
    : m_Radius(a_Radius), ICollider(a_Center)
{
}

tabi::SphereCollider::SphereCollider(const float a_Radius, const Transform& a_WorldTransform)
    : m_Radius(a_Radius), ICollider(a_WorldTransform)
{
}

tabi::vec3 tabi::SphereCollider::GetFurthestPointInDirection(const tabi::vec3& a_Direction) const
{
    vec3 rotatedScale = m_Transform.m_Scale;
    
    if (m_Transform.m_Scale != tabi::vec3{ 1.0f, 1.0f, 1.0f })
    {
        // Rotate the scale based on the collider's rotation to make sure the furthest point is scaled in the correct direction
        rotatedScale = mat4::SetRotation(mat4::Identity(), m_Transform.m_EulerRotation)* m_Transform.m_Scale;
    }

    return m_Transform.m_Position + vec3::Normalize(a_Direction) * m_Radius * rotatedScale;
}

void tabi::SphereCollider::SetRadius(const float a_Radius)
{
    m_Radius = a_Radius;
}

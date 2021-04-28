#include "Colliders/Sphere.h"

tabi::SphereCollider::SphereCollider()
    : ICollider(tabi::vec3{ 0.0f, 0.0f, 0.0f })
{
    SetRadius(0.5f);
}

tabi::SphereCollider::SphereCollider(const float a_Radius)
    : ICollider(tabi::vec3{ 0.0f, 0.0f, 0.0f })
{
    SetRadius(a_Radius);
}

tabi::SphereCollider::SphereCollider(const float a_Radius, const vec3& a_Center)
    : ICollider(a_Center)
{
    SetRadius(a_Radius);
}

tabi::SphereCollider::SphereCollider(const float a_Radius, const Transform& a_WorldTransform)
    : ICollider(a_WorldTransform)
{
    SetRadius(a_Radius);
}

tabi::vec3 tabi::SphereCollider::GetFurthestPointInDirection(const tabi::vec3& a_Direction) const
{
    const vec3 searchDirection = mat4::SetInverseRotation(mat4::Identity(), m_Transform.m_EulerRotation) * a_Direction;

    return m_Transform.m_Position + mat4::SetRotation(mat4::Identity(), m_Transform.m_EulerRotation) * (vec3::Normalize(searchDirection) * m_Radius * m_Transform.m_Scale);
}

void tabi::SphereCollider::SetRadius(const float a_Radius)
{
    TABI_ASSERT(a_Radius >= 0.0f);

    m_Radius = a_Radius;
    m_BroadPhaseSphereRadius = a_Radius;
}

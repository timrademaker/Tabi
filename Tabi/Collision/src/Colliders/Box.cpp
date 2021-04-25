#include "Colliders/Box.h"

tabi::BoxCollider::BoxCollider()
    : HullCollider(tabi::vector<tabi::vec3>())
{
    SetHalfBoxExtents(tabi::vec3{ 0.5f, 0.5f, 0.5f });
}

tabi::BoxCollider::BoxCollider(const tabi::vec3& a_HalfBoxExtents)
    : HullCollider(tabi::vector<tabi::vec3>())
{
    SetHalfBoxExtents(a_HalfBoxExtents);
}

tabi::BoxCollider::BoxCollider(const tabi::vec3& a_HalfBoxExtents, const Transform& a_WorldTransform)
    : HullCollider(tabi::vector<tabi::vec3>(), a_WorldTransform)
{
    SetHalfBoxExtents(a_HalfBoxExtents);
}

tabi::BoxCollider::BoxCollider(const tabi::vec3& a_HalfBoxExtents, const vec3& a_WorldPosition)
    : HullCollider(tabi::vector<tabi::vec3>(), a_WorldPosition)
{
    SetHalfBoxExtents(a_HalfBoxExtents);
}

void tabi::BoxCollider::SetHalfBoxExtents(const tabi::vec3& a_HalfBoxExtents)
{
    // Make sure the box extents are positive
    TABI_ASSERT(a_HalfBoxExtents.Dot(tabi::vec3{ 1.0f, 1.0f, 1.0f }) > 0.0f);

    m_Vertices.clear();
    m_Vertices.reserve(8);

    m_Vertices.push_back({ a_HalfBoxExtents.x,  a_HalfBoxExtents.y,  a_HalfBoxExtents.z });
    m_Vertices.push_back({ a_HalfBoxExtents.x,  a_HalfBoxExtents.y, -a_HalfBoxExtents.z });
    m_Vertices.push_back({ a_HalfBoxExtents.x, -a_HalfBoxExtents.y, -a_HalfBoxExtents.z });
    m_Vertices.push_back({ a_HalfBoxExtents.x, -a_HalfBoxExtents.y,  a_HalfBoxExtents.z });
    m_Vertices.push_back({ -a_HalfBoxExtents.x,  a_HalfBoxExtents.y,  a_HalfBoxExtents.z });
    m_Vertices.push_back({ -a_HalfBoxExtents.x,  a_HalfBoxExtents.y, -a_HalfBoxExtents.z });
    m_Vertices.push_back({ -a_HalfBoxExtents.x, -a_HalfBoxExtents.y, -a_HalfBoxExtents.z });
    m_Vertices.push_back({ -a_HalfBoxExtents.x, -a_HalfBoxExtents.y,  a_HalfBoxExtents.z });
}

void tabi::BoxCollider::SetBoxExtents(const tabi::vec3& a_BoxExtents)
{
    SetHalfBoxExtents(a_BoxExtents / 2.0f);
}

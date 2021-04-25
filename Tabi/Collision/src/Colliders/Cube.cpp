#include "Colliders/Cube.h"

tabi::CubeCollider::CubeCollider()
    : HullCollider(tabi::vector<tabi::vec3>())
{
    SetHalfBoxExtents(tabi::vec3{ 0.5f, 0.5f, 0.5f });
}

tabi::CubeCollider::CubeCollider(const tabi::vec3& a_HalfBoxExtents)
    : HullCollider(tabi::vector<tabi::vec3>())
{
    SetHalfBoxExtents(a_HalfBoxExtents);
}

tabi::CubeCollider::CubeCollider(const tabi::vec3& a_HalfBoxExtents, const Transform& a_WorldTransform)
    : HullCollider(tabi::vector<tabi::vec3>(), a_WorldTransform)
{
    SetHalfBoxExtents(a_HalfBoxExtents);
}

tabi::CubeCollider::CubeCollider(const tabi::vec3& a_HalfBoxExtents, const vec3& a_WorldPosition)
    : HullCollider(tabi::vector<tabi::vec3>(), a_WorldPosition)
{
    SetHalfBoxExtents(a_HalfBoxExtents);
}

void tabi::CubeCollider::SetHalfBoxExtents(const tabi::vec3& a_HalfBoxExtents)
{
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

void tabi::CubeCollider::SetBoxExtents(const tabi::vec3& a_BoxExtents)
{
    SetHalfBoxExtents(a_BoxExtents / 2.0f);
}

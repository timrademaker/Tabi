#include "Colliders/Hull.h"

tabi::HullCollider::HullCollider(const tabi::vector<vec3>& a_Vertices)
    : m_Vertices(a_Vertices)
{
}

tabi::HullCollider::HullCollider(const tabi::vector<vec3>& a_Vertices, const Transform& a_WorldTransform)
    : m_Vertices(a_Vertices), ICollider(a_WorldTransform)
{
}

tabi::HullCollider::HullCollider(const tabi::vector<vec3>& a_Vertices, const vec3& a_WorldPosition)
    : m_Vertices(a_Vertices), ICollider(a_WorldPosition)
{
}

tabi::vec3 tabi::HullCollider::GetFurthestPointInDirection(const vec3& a_Direction) const
{
    // Rotate the direction vector based on the collider's rotation
    // Rotate in the opposite direction, as this prevents us from having to rotate all points instead
    const vec3 searchDirection = mat4::SetUnRotation(mat4::Identity(), m_Transform.m_EulerRotation) * a_Direction;

    int furthestPointIndex = -1;
    float furthestPointDistance = FLT_MIN;

    for (int vertexIndex = 0; vertexIndex < m_Vertices.size(); ++vertexIndex)
    {
        const vec3& vertex = m_Vertices[vertexIndex];

        const float distance = searchDirection.Dot(vertex);
        if (distance > furthestPointDistance)
        {
            furthestPointIndex = vertexIndex;
            furthestPointDistance = distance;
        }
    }

    return m_Transform.m_Position + mat4::SetRotation(mat4::Identity(), m_Transform.m_EulerRotation) * (m_Vertices[furthestPointIndex] * m_Transform.m_Scale);
}


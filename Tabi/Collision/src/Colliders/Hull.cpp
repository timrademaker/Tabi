#include "Colliders/Hull.h"

tabi::HullCollider::HullCollider(tabi::vector<vec3>& a_Vertices)
    : m_Vertices(a_Vertices)
{
}

tabi::HullCollider::HullCollider(tabi::vector<vec3>& a_Vertices, Transform a_WorldTransform)
    : m_Vertices(a_Vertices), ICollider(a_WorldTransform)
{
}

tabi::HullCollider::HullCollider(tabi::vector<vec3>& a_Vertices, vec3 a_WorldPosition)
    : m_Vertices(a_Vertices), ICollider(a_WorldPosition)
{
}

tabi::vec3 tabi::HullCollider::GetFurthestPointInDirection(const vec3& a_Direction) const
{
    int furthestPointIndex = -1;
    float furthestPointDistance = FLT_MIN;

    for (int vertexIndex = 0; vertexIndex < m_Vertices.size(); ++vertexIndex)
    {
        const vec3& vertex = m_Vertices[vertexIndex];

        const float distance = a_Direction.Dot(vertex);
        if (distance > furthestPointDistance)
        {
            furthestPointIndex = vertexIndex;
            furthestPointDistance = distance;
        }
    }

    return m_Transform.m_Position + (m_Vertices[furthestPointIndex] * m_Transform.m_Scale);
}


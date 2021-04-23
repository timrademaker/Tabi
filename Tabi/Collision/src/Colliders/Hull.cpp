#include "Colliders/Hull.h"

tabi::HullCollider::HullCollider(tabi::vector<vec3>& a_Vertices, vec3 a_WorldPosition)
    : m_Vertices(a_Vertices), ICollider(a_WorldPosition)
{
    m_RelativeCenter = FindHullCenter();
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

    return m_WorldPosition + m_RelativeCenter + m_Vertices[furthestPointIndex];
}

tabi::vec3 tabi::HullCollider::FindHullCenter()
{
    // Determine the average position of all vertices. Not completely accurate, but it should do the trick
    vec3 accumulatedVertexPosition;
    
    for (const vec3& vertex : m_Vertices)
    {
        accumulatedVertexPosition += vertex;
    }
    
    return accumulatedVertexPosition / static_cast<float>(m_Vertices.size());
}

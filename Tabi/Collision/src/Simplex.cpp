#include "Simplex.h"

tabi::Simplex::Simplex(const size_t a_ExpectedNumPoints)
{
    m_Points.reserve(a_ExpectedNumPoints);
}

void tabi::Simplex::AddPoint(const tabi::vec3& a_Point)
{
    m_Points.push_back(a_Point);
}

bool tabi::Simplex::ContainsOrigin(tabi::vec3& a_DirectionTowardsOrigin)
{
    if (m_Points.size() == 4)
    {
        // TODO: Check if origin contained 
    }
    // Origin can't be contained yet as the simplex is not a tetrahedron
    else if (m_Points.size() == 3)
    {
        // TODO: Find direction towards origin
    }
    else if (m_Points.size() == 2)  // Line
    {
        // Find the normal of the line between pointA and pointB in the direction of the origin
        vec3 AB = m_Points[1] - m_Points[0];

        // Use the vector triple product to find the direction towards the origin
        a_DirectionTowardsOrigin = AB.Cross(-m_Points[0]).Cross(AB);
    }

    return false;
}

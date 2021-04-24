#include "ThreeSimplex.h"

tabi::ThreeSimplex::ThreeSimplex()
    : m_NumPoints(0)
{
}

bool tabi::ThreeSimplex::AddPoint(const tabi::vec3& a_Point)
{
    if (m_NumPoints < 4)
    {
        m_Points[m_NumPoints] = a_Point;
        ++m_NumPoints;
        return true;
    }
    else
    {
        return false;
    }
}

bool tabi::ThreeSimplex::ContainsOrigin(tabi::vec3& a_DirectionTowardsOrigin)
{
    if (m_NumPoints == 4)
    {
        // TODO: Check if origin contained 
    }
    // Origin can't be contained yet as the simplex is not a tetrahedron
    else if (m_NumPoints == 3)
    {
        // TODO: Find direction towards origin
    }
    else if (m_NumPoints == 2)  // Line
    {
        // Find the normal of the line between pointA and pointB in the direction of the origin
        vec3 AB = m_Points[1] - m_Points[0];

        // Use the vector triple product to find the direction towards the origin
        a_DirectionTowardsOrigin = AB.Cross(-m_Points[0]).Cross(AB);
    }

    return false;
}

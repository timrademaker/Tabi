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
    if (m_NumPoints == 4)   // Tetrahedron
    {
        // Check if the origin is inside the tetrahedron

        const vec3 ad = d - a;
        const vec3 bd = d - b;
        const vec3 cd = d - c;
        const vec3 d0 = -d;

        const vec3 abdNormal = ad.Cross(bd);
        const vec3 acdNormal = ad.Cross(bd);
        const vec3 bcdNormal = bd.Cross(cd);

        if (abdNormal.Dot(d0) < 0.0f)
        {
            // Outside ABD
            a_DirectionTowardsOrigin = abdNormal;
        }
        else if (acdNormal.Dot(d0) < 0.0f)
        {
            // Outside ACD
            a_DirectionTowardsOrigin = acdNormal;
        }
        else if (bcdNormal.Dot(d0) < 0.0f)
        {
            // Outside BCD
            a_DirectionTowardsOrigin = bcdNormal;
        }
        else
        {
            return true;
        }
    }
    // Origin can't be contained yet as the simplex is not a tetrahedron
    else if (m_NumPoints == 3)  // Triangle
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

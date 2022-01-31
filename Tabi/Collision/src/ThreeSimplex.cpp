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

bool tabi::ThreeSimplex::EvolveSimplex(tabi::vec3& a_DirectionTowardsOrigin)
{
    if (m_NumPoints == 4)   // Tetrahedron
    {
        // Check if the origin is inside the tetrahedron

        const vec3 ad = d - a;
        const vec3 bd = d - b;
        const vec3 cd = d - c;
        const vec3 d0 = -d;

        const vec3 abdNormal = ad.Cross(bd);
        const vec3 acdNormal = cd.Cross(ad);
        const vec3 bcdNormal = bd.Cross(cd);

        if (abdNormal.Dot(d0) > 0.0f)
        {
            // Outside ABD
            a_DirectionTowardsOrigin = abdNormal;

            // Remove C
            c = m_Points[3];
            m_NumPoints -= 1;
        }
        else if (acdNormal.Dot(d0) > 0.0f)
        {
            // Outside ACD
            a_DirectionTowardsOrigin = acdNormal;

            // Remove B
            b = m_Points[3];
            m_NumPoints -= 1;
        }
        else if (bcdNormal.Dot(d0) > 0.0f)
        {
            // Outside BCD
            a_DirectionTowardsOrigin = bcdNormal;

            // Remove A
            a = m_Points[3];
            m_NumPoints -= 1;
        }
        else
        {
            return true;
        }
    }
    // Origin can't be contained yet as the simplex is not a tetrahedron
    else if (m_NumPoints == 3)  // Triangle
    {
        // Find the normal of the triangle in the direction of the origin
        const vec3 ab = b - a;
        const vec3 ac = c - a;

        a_DirectionTowardsOrigin = ac.Cross(ab);
        if (a_DirectionTowardsOrigin.Dot(-a) < 0.0f)
        {
            a_DirectionTowardsOrigin = -a_DirectionTowardsOrigin;
        }
    }
    else if (m_NumPoints == 2)  // Line
    {
        // Find the normal of the line between point A and point B in the direction of the origin
        const vec3 ba = a - b;
        const vec3 b0 = -b;

        // Use the vector triple product to find the normal towards the origin
        const vec3 tmp = ba.Cross(b0);

        if (tmp.LengthSquared() != 0.0f)
        {
            a_DirectionTowardsOrigin = tmp.Cross(ba);
        }
        else
        {
            // As this class is specifically meant to be used in GJK.cpp, we can assume that B lies past the origin
            // And because we searched in the direction of the origin to find B, the origin can't lie beyond A.
            // If this wasn't certain, we'd have to check if(ba.Dot(b0) < ba.Dot(ba))
                
            // Origin lies on BA
            return true;
        }
    }
    else
    {
        a_DirectionTowardsOrigin = -a;
    }

    return false;
}

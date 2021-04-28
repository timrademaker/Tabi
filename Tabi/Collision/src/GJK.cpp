#include "GJK.h"

#include "ThreeSimplex.h"

#include "Colliders/ICollider.h"

bool tabi::GJK::CollidersAreOverlapping(const ICollider* a_Collider1, const ICollider* a_Collider2)
{
    vec3 direction = a_Collider1->GetPosition() - a_Collider2->GetPosition();

    if (direction.LengthSquared() == 0)
    {
        // The colliders are placed on top of each other
        return true;
        
        // I can't think of any issues with this now (unless the origin of a collider can be outside of the collider itself),
        // but this return might have to be removed and an arbitrary direction will have to be used instead if it turns out this causes issues
    }

    ThreeSimplex simplex;

    vec3 pointA = Support(a_Collider1, a_Collider2, direction);
    simplex.AddPoint(pointA);

    direction = -pointA; // New direction is from A towards the origin

    // Build a 3-simplex
    for (size_t iteration = 0; iteration < s_MaxIterations; ++iteration)
    {
        // Find a point in the new direction
        vec3 newPoint = Support(a_Collider1, a_Collider2, direction);

        // Check if the point is past the origin
        if (newPoint.Dot(direction) < 0)
        {
            // No intersection possible as the origin falls outside of the Minkowski sum
            return false;
        }

        simplex.AddPoint(newPoint);

        if (simplex.EvolveSimplex(direction))
        {
            // Shapes overlap
            return true;
        }
    }

    return false;
}

tabi::vec3 tabi::GJK::Support(const ICollider* a_Collider1, const ICollider* a_Collider2, const vec3& a_Direction)
{
    const vec3 pointA = a_Collider1->GetFurthestPointInDirection(a_Direction);
    const vec3 pointB = a_Collider2->GetFurthestPointInDirection(-a_Direction);

    return pointA - pointB;
}

#include "GJK.h"

#include "Simplex.h"

#include "Colliders/ICollider.h"

bool tabi::GJK::CollidersAreOverlapping(const ICollider* a_Collider1, const ICollider* a_Collider2)
{
    Simplex simplex;

    vec3 direction; // Arbitrary direction
    vec3 pointA = Support(a_Collider1, a_Collider2, direction);
    simplex.AddPoint(pointA);

    direction = -pointA; // New direction is from A towards the origin

    // Build a 3-simplex
    for (int i = 0; i < 3; ++i)
    {
        // Find a point in the new direction
        vec3 newPoint = Support(a_Collider1, a_Collider2, direction);

        // Check if the point is past the origin
        if (newPoint.Dot(direction) < 0)
        {
            // No intersection possible as the origin falls outside of the Minkowski shape
            return false;
        }

        simplex.AddPoint(newPoint);

        if (simplex.ContainsOrigin(direction))
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

    // TODO: Is this the correct order?
    return pointB - pointA;
}

#pragma once

#include <Math/vec3.h>

namespace tabi
{
    class GJK
    {
    public:
        /**
         * Check if two colliders are overlapping
         * @param a_Collider1 The collider that is being checked for overlaps with a_Collider2
         * @param a_Collider2 The collider that is being checked for overlaps with a_Collider1
         * @return True if a_Collider1 and a_Collider2 overlap
         */
        static bool CollidersAreOverlapping(const class ICollider* a_Collider1, const class ICollider* a_Collider2);

    private:
        GJK() = default;

        /**
         * GJK support function
         * @param a_Collider1 The collider that is being checked for overlaps with a_Collider2
         * @param a_Collider2 The collider that is being checked for overlaps with a_Collider1
         * @param a_Direction The direction in which to find the furthest point in the Minkowski sum
         * @return A vertex of the Minkowski sum
         */
        static vec3 Support(const ICollider* a_Collider1, const ICollider* a_Collider2, const vec3& a_Direction);
    };
}

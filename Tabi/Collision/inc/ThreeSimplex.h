#pragma once

#include <Math/vec3.h>

namespace tabi
{
    class ThreeSimplex
    {
    public:
        ThreeSimplex();
        ~ThreeSimplex() = default;

        /**
         * Add a point to the simplex
         * @param a_Point The point to add
         * @return True if the point was successfully added
         */
        bool AddPoint(const tabi::vec3& a_Point);

        /**
         * Check if the simplex contains the origin
         * @param a_DirectionTowardsOrigin Will be set to the direction from the simplex towards the origin if the origin is not contained and the simplex has less than 4 points
         * @return True if the simplex contains the origin
         */
        bool ContainsOrigin(tabi::vec3& a_DirectionTowardsOrigin);

    private:
        tabi::vec3 m_Points[4];
        int m_NumPoints;
    };
}

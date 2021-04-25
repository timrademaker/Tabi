#pragma once

#include <Math/vec3.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING

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
         * Evolve the simplex and check if it contains the origin
         * @param a_DirectionTowardsOrigin Will be set to the direction from the simplex towards the origin if the origin is not contained and the simplex has less than 4 points
         * @return True if the simplex contains the origin
         */
        bool EvolveSimplex(tabi::vec3& a_DirectionTowardsOrigin);

    private:
        union
        {
            tabi::vec3 m_Points[4];
            struct
            {
                tabi::vec3 a;
                tabi::vec3 b;
                tabi::vec3 c;
                tabi::vec3 d;
            };
            struct
            {
                tabi::vec3 m_A;
                tabi::vec3 m_B;
                tabi::vec3 m_C;
                tabi::vec3 m_D;
            };
        };

        int m_NumPoints;
    };
}
DISABLE_WARNING_POP

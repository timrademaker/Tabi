#pragma once

#include <Math/vec3.h>
#include <TabiContainers.h>

namespace tabi
{
    class Simplex
    {
    public:
        Simplex() = default;
        Simplex(const size_t a_ExpectedNumPoints);
        ~Simplex() = default;

        void AddPoint(const tabi::vec3& a_Point);

        /**
         * Check if the simplex contains the origin
         * @param a_DirectionTowardsOrigin Will be set to the direction from the simplex towards the origin if the origin is not contained and the simplex has less than 4 points
         * @return True if the simplex contains the origin
         */
        bool ContainsOrigin(tabi::vec3& a_DirectionTowardsOrigin);

    private:
        tabi::vector<tabi::vec3> m_Points;
    };
}

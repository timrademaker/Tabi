#pragma once

#include "Hull.h"

namespace tabi
{
    class BoxCollider : public HullCollider
    {
    public:
        BoxCollider();
        BoxCollider(const tabi::vec3& a_HalfBoxExtents);
        BoxCollider(const tabi::vec3& a_HalfBoxExtents, const Transform& a_WorldTransform);
        BoxCollider(const tabi::vec3& a_HalfBoxExtents, const vec3& a_WorldPosition);
        virtual ~BoxCollider() override = default;

        /**
         * Set the half box extents for the cube
         * @param a_HalfBoxExtents The distance from the center of the box towards a corner
         */
        void SetHalfBoxExtents(const tabi::vec3& a_HalfBoxExtents);

        /**
         * Set the box extents for the cube
         * @param a_BoxExtents The extents of the box
         */
        void SetBoxExtents(const tabi::vec3& a_BoxExtents);
    };
}

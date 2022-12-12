#pragma once

#include "ICollider.h"

namespace tabi
{
    class SphereCollider : public ICollider
    {
    public:
        SphereCollider();
        SphereCollider(const float a_Radius);
        SphereCollider(const float a_Radius, const vec3& a_Center);
        SphereCollider(const float a_Radius, const Transform& a_WorldTransform);
        virtual ~SphereCollider() override = default;

        virtual vec3 GetFurthestPointInDirection(const vec3& a_Direction) const override;

        /**
         * Get the sphere collider's radius
         * @return The sphere collider's radius
         */
        TABI_INLINE float GetRadius() const
        {
            return m_Radius;
        };
        /**
         * Set the sphere collider's radius
         * @param a_Radius The new radius of the sphere collider
         */
        void SetRadius(const float a_Radius);

    private:
        /** The sphere's radius */
        float m_Radius;
    };
}

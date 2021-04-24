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

        virtual vec3 GetFurthestPointInDirection(const vec3& a_Direction) const override;

        TABI_INLINE float GetRadius()
        {
            return m_Radius;
        };
        void SetRadius(const float a_Radius);

    private:
        float m_Radius;
    };
}

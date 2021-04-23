#pragma once

#include <Math/vec3.h>

namespace tabi
{
    class ICollider
    {
    public:
        ICollider();
        ICollider(const vec3& a_WorldPosition);
        ~ICollider() = default;

        virtual vec3 GetFurthestPointInDirection(const vec3& a_Direction) const = 0;

        void SetWorldPosition(const vec3& a_WorldPosition);

    protected:
        vec3 m_WorldPosition;
    };
}

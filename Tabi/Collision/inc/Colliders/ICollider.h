#pragma once

#include <Components/Transform.h>

namespace tabi
{
    class ICollider
    {
    public:
        ICollider();
        ICollider(const Transform& a_WorldTransform);
        ICollider(const vec3& a_WorldPosition);
        ~ICollider() = default;

        /**
         * Get the furthest point in a given direction
         * @param a_Direction The direction in which to find the furthest point on the collider
         * @return The furthest point in the given direction
         */
        virtual vec3 GetFurthestPointInDirection(const vec3& a_Direction) const = 0;

        /**
         * Set the world position of the collider
         * @param a_WorldPosition The world position of this collider's center
         */
        void SetWorldPosition(const vec3& a_WorldPosition);
        /**
         * Set the scale of the collider in world space
         * @param a_WorldScale The scale of this collider in world space
         */
        void SetWorldScale(const vec3& a_WorldScale);
        /**
         * Set the rotation of the collider in world space
         * @param a_WorldRotation The rotation of this collider in world space
         */
        void SetWorldRotation(const vec3& a_WorldRotation);
        /**
         * Set the transform of the collider in world space
         * @param a_WorldTransform The transform of this collider in world space
         */
        void SetWorldTransfrom(const Transform& a_WorldTransform);

        /**
         * Get the position of the collider
         * @return The position of the collider
         */
        vec3 GetPosition() const;

    protected:
        Transform m_Transform;
    };
}

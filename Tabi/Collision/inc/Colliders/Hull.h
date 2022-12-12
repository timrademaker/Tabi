#pragma once

#include "ICollider.h"

#include <TabiContainers.h>

namespace tabi
{
    class HullCollider : public ICollider
    {
    public:
        HullCollider(const tabi::vector<vec3>& a_Vertices);
        HullCollider(const tabi::vector<vec3>& a_Vertices, const Transform& a_WorldTransform);
        HullCollider(const tabi::vector<vec3>& a_Vertices, const vec3& a_WorldPosition);
        virtual ~HullCollider() override = default;

        virtual vec3 GetFurthestPointInDirection(const vec3& a_Direction) const override;

    private:
        /**
         * Get the distance to the vertex furthest away from the hull's center. Used for broad phase sphere radius.
         * @return The distance to the vertex furthest away from the hull's center
         */
        float GetFurthestVertexDistance() const;

    protected:
        /** All of the vertices making up the hull */
        tabi::vector<vec3> m_Vertices;
    };
}

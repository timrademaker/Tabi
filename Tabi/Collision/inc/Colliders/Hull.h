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
        ~HullCollider() = default;

        virtual vec3 GetFurthestPointInDirection(const vec3& a_Direction) const override;

    private:
        float GetFurthestVertexDistance() const;

    protected:
        /** All of the vertices making up the hull */
        tabi::vector<vec3> m_Vertices;
    };
}

#pragma once

#include "ICollider.h"

#include <TabiContainers.h>

namespace tabi
{
    class HullCollider : public ICollider
    {
    public:
        HullCollider(tabi::vector<vec3>& a_Vertices, vec3 a_WorldPosition);
        ~HullCollider() = default;

        virtual vec3 GetFurthestPointInDirection(const vec3& a_Direction) const override;

    private:
        vec3 FindHullCenter();

    protected:
        vec3 m_RelativeCenter;
        tabi::vector<vec3> m_Vertices;
    };
}

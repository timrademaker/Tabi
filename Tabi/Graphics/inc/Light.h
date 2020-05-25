#pragma once

#include <vec3.h>

namespace tabi
{
    enum class ELightType
    {
        Direction,
        Point,
        Spot
    };

    class Light
    {
    public:
        ELightType m_LightType;
        tabi::math::vec3 m_Color;
        float m_Intensity;

        tabi::math::vec3 m_Position;
        tabi::math::vec3 m_Direction;
    };
}
#pragma once

#include <TabiMath.h>

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
        tabi::maths::vec3 m_Color;
        float m_Intensity;

        tabi::maths::vec3 m_Position;
        tabi::maths::vec3 m_Direction;
    };
}
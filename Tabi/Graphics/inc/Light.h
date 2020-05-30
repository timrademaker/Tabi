#pragma once

#include <Math/vec3.h>

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
        tabi::vec3 m_Color;
        float m_Intensity;

        tabi::vec3 m_Position;
        tabi::vec3 m_Direction;
    };
}
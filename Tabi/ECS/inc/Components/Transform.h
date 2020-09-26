#pragma once

#include <Math/vec3.h>

namespace tabi
{
    struct Transform
    {
        tabi::vec3 m_Position;
        tabi::vec3 m_Scale;
        tabi::vec3 m_EulerRotation;
    };
}
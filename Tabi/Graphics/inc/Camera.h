#pragma once

#include <vec3.h>

enum class ECameraType
{
    Perspective,
    Orthographic,
};

namespace tabi
{
    class Camera
    {
    public:
//        Camera() = default;
//        ~Camera() = default;

        float m_Near = 0.05f;
        float m_Far = 1000.f;
        float m_FoV = 60.f;
        
        //glm::mat4 m_View;

        ECameraType m_CameraType;

        tabi::math::vec3 m_Position;
    };

}